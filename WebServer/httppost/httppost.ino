
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

//const char* ssid = "MPJAC82";
//const char*password= "N0t14u2c.82";
const char* ssid = "ROXS24";
const char*password= "capstone";


ESP8266WebServer server(80);

int value = 0;

void handleGet() {
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["value"] = value;
  String jsonStr;
  serializeJson(jsonDoc, jsonStr);
  server.send(200, "application/json", jsonStr);
}

void handlePut() {
  String body = server.arg("plain");
  StaticJsonDocument<200> jsonDoc;
  DeserializationError error = deserializeJson(jsonDoc, body);
  if (error) {
    server.send(400, "text/plain", "Invalid JSON");
    return;
  }
  int newValue = jsonDoc["value"];
  value = newValue;
  server.send(204);
}

void handlePatch() {
  String body = server.arg("plain");
  StaticJsonDocument<200> jsonDoc;
  DeserializationError error = deserializeJson(jsonDoc, body);
  if (error) {
    server.send(400, "text/plain", "Invalid JSON");
    return;
  }
  int newValue = jsonDoc["value"];
  value = newValue;
  server.send(204);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/value", HTTP_GET, handleGet);
  server.on("/value", HTTP_PUT, handlePut);
  server.on("/value", HTTP_PATCH, handlePatch);
  server.begin();
}

void loop() {
  server.handleClient();
}
