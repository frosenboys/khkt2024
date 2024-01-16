// Libraries
#include <SHT3x.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Wire.h>

// Define
#define RELAY_PIN 12

SHT3x Sensor;
const char* ssid = "Selee";
const char* password = "12345678";
const char* serverName = "https://datbing.click/post.php";  // Server URL
long long connected=0;

// Main
void setup(){
  pinMode(RELAY_PIN,OUTPUT);
  Serial.begin(115200);
  Sensor.Begin();

  Serial.println("Started");
  
  int wait=0;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
    wait++;
    if (wait == 20) break;
  }
  if (WiFi.status() == WL_CONNECTED){
    connected = 1;
    Serial.print("Connected");
  }
  else Serial.print("Connect failed");
}
int k=0;
void loop(){
  Sensor.UpdateData();
  if (Sensor.GetTemperature() >= 70 || Sensor.GetRelHumidity() >= 70) fan_on();
  else fan_off();
  if (Sensor.GetTemperature() >= 100 && k == 0){
    alert("Nhiệt độ quá nóng");
    k++;
  }
}

// Functions
void fan_on(){
  digitalWrite(RELAY_PIN, HIGH);
}

void fan_off(){
  digitalWrite(RELAY_PIN, LOW);
}

void alert(String content){
  if(connected){
      HTTPClient https;
      WiFiClientSecure *client = new WiFiClientSecure;
      client->setInsecure();
      https.begin(*client, serverName);
      https.addHeader("Content-Type", "application/x-www-form-urlencoded");

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
}

