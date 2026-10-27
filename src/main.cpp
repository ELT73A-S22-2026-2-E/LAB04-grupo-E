#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char *WIFI_SSID  = "Wokwi-GUEST";
const char *WIFI_PASS = "";
// const char* WIFI_SSID = "IoT-Broker";
// const char* WIFI_PASS = "ESP32IoTLab";
const char* MQTT_HOST = "broker.hivemq.com";
const int   MQTT_PORT = 1883;

WiFiClient   wifiClient;
PubSubClient mqtt(wifiClient);

void conectaWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) { delay(300); Serial.print("."); }
  Serial.print("\nWiFi OK, IP: "); Serial.println(WiFi.localIP());
}

void conectaMQTT() {
  mqtt.setServer(MQTT_HOST, MQTT_PORT);
  while (!mqtt.connected()) {
    String clientId = "esp32-" + String(random(0xffff), HEX);
    Serial.print("Conectando ao broker MQTT... ");
    if (mqtt.connect(clientId.c_str())) {
      Serial.println("conectado!");
    } else {
      Serial.print("falhou (rc="); Serial.print(mqtt.state());
      Serial.println("), nova tentativa em 2s");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  conectaWiFi();
  conectaMQTT();
}

void loop() {
  mqtt.loop();
}