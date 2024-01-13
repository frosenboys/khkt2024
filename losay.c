#include <SHT3x.h>
#include <Wifi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Wire.h>

#define RELAY_PIN 12

SHT3x Sensor;
const char* ssid = "Selee";
const char* password = "12345678";
const char*  serverName = "https://datbing.click/";  // Server URL
long long count;

void setup(){
  pinMode(RELAY_PIN);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  int wait=0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
    wait++;
    if (wait == 20) break;
  }
  if (wait == 20) Serial.print("Connected");
  else Serial.println("Failed to connect to " + ssid);
}

void fan_on(){
  digitalWrite(RELAY_PIN, HIGH);
}

void fan_off(){
  digitalWrite(RELAY_PIN, LOW);
}

void alert(String content){
  count++;
  if(WiFi.status()== WL_CONNECTED && count == 1){
      WiFiClient client;
      HTTPClient http;
    
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "content=" + String(content);           
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
      if (httpResponseCode > 0){
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      }
      else{
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}

void loop(){
  Sensor.UpdateData();
  if (Sensor.GetTemperature() >= 70 || Sensor.GetRelHumidity() >= 70) fan_on();
  else fan_off();
  
}
