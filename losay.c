// Libraries
#include <SHT3x.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <WebServer.h>

// Define
#define RELAY_PIN 4
const char* ssid, password;
const char* serverName = "https://losay.steambinhlong.edu.vn/post.php";  // Server URL
const char* Essid = "Lo_Say";
const char* Epassword = "123456789";
int connected=0;
SHT3x Sensor;
WebServer server(80);

// Hàm xử lý khi có yêu cầu đến trang web
void handleRoot() {
  String html = "<html><head><title>Cấu hình WiFi</title></head><body>";
  html += "<form action=\"/setup\" method=\"post\">";
  html += "SSID: <input type=\"text\" name=\"ssid\" value=\"\"><br>";
  html += "Mật khẩu: <input type=\"password\" name=\"pass\" value=\"\"><br>";
  html += "<input type=\"submit\" value=\"Lưu\">";
  html += "</form></body></html>";
  server.send(200, "text/html", html);
}

// Sấy dẻo: 40-70°C
// Sấy khô: 60-80°C
// Sấy giòn: 70-90°C

// Hàm xử lý khi người dùng nhập thông tin WiFi
void handleSetup() {
  if (server.hasArg("ssid") && server.hasArg("pass")) {
    String ssid_new = server.arg("ssid");
    String pass_new = server.arg("pass");
    
    // Lưu thông tin WiFi mới
    WiFi.begin(ssid_new.c_str(), pass_new.c_str());
    
    // Hiển thị thông báo kết nối
    server.send(200, "text/html", "<p>Đang kết nối WiFi...</p>");
    
    // Chờ kết nối WiFi
    int wait = 0, failed = 0;
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      server.send(200, "text/html", "<p>Đang kết nối WiFi...</p>");
      wait++;
      if (wait > 20){
        server.send(200, "text/html", "<p style='color:red'>Kết nối WiFi không thành công!</p>");
        failed = 1;
        break;
      }
    }
    // Thông báo kết nối thành công
    if (failed == 0){
      server.send(200, "text/html", "<p style='color:green'>Kết nối WiFi thành công!</p>");
      connected = 1;
      server.stop();
    }
  } else {
    // Lỗi nhập thông tin
    server.send(400, "text/html", "<p style='color:red'>Lỗi: Vui lòng nhập đủ thông tin!</p>");
  }
}


// Main
void setup(){
  pinMode(RELAY_PIN,OUTPUT);
  Serial.begin(115200);
  Sensor.Begin();
  Serial.println("Started");

  WiFi.mode(WIFI_STA);
  server.begin();
  server.on("/", handleRoot);
  server.on("/setup", handleSetup);
}

void loop(){
  static uint32_t time = millis();
  Sensor.UpdateData();
  int temperature  = Sensor.GetTemperature();
  if (Sensor.GetTemperature() >= 70 || Sensor.GetRelHumidity() >= 70) fan_on();
  else fan_off();
  
  // Alert when connected
  if (connected) {
    if (millis() - time > 10000){
      time = millis();
      if (temperature >= 70) alert("Nóng|" + String(temperature));
      else alert("Ổn định|" + String(temperature));
    }
  }
  else{
    server.handleClient();
  }
}

// Functions
void fan_on(){
  digitalWrite(RELAY_PIN, HIGH);
}

void fan_off(){
  digitalWrite(RELAY_PIN, LOW);
}

HTTPClient https;
WiFiClientSecure *client = new WiFiClientSecure;
client->setInsecure();
https.begin(*client, serverName);
https.addHeader("Content-Type", "application/x-www-form-urlencoded");

void alert(String content){
    // Send data
    String httpRequestData = "content=" + String(content);
    int httpResponseCode = https.POST(httpRequestData);

    // Status POST
    if (httpResponseCode > 0){
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else{
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // End
    https.end();
  
}
