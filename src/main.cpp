#include <Arduino.h>
#include <WiFi.h>

const char *WIFI_SSID  = "Wokwi-GUEST";
const char *WIFI_PASS = "";
// const char* WIFI_SSID = "IoT-Broker";
// const char* WIFI_PASS = "ESP32IoTLab";

void conectaWiFi() {
  Serial.print("Conectando a "); Serial.println(WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado! IP: "); Serial.println(WiFi.localIP());
  Serial.print("RSSI: ");           Serial.println(WiFi.RSSI());
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  conectaWiFi();
}

void loop() {}