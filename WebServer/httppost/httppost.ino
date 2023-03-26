
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

// create prototypes for functions
void moveZ();
float zeroZ();
float stepMotor();
bool ledToggle();
//void handleGetPR();

const char* ssid = "MPJAC82";
const char*password= "N0t14u2c.82";
//const char* ssid = "ROXS24";
//const char*password= "capstone";



// Initial constant paramters
float zCurrent = 463;   // in mm
bool ledStatus = false; // false = off, true = on

// Define pinouts for digital in/out & analog read

const int stepPin = 2;     // to step pin on motor driver
const int dirPin = 10;      // to direction pin on motor driver
const int limitPin = 5;   // from limit switch input
const int ledPin = 4;     // to relay for LED

const int PR = A0;   // from photoresistor circuit

ESP8266WebServer server(80);

int speed = 0;
int goalpos = 0;

void handleGet() {
  StaticJsonDocument<400> jsonDoc;
  jsonDoc["speed"] = speed;
  jsonDoc["goalpos"] = goalpos;
  jsonDoc["zCurrent"] = zCurrent;
  jsonDoc["PRInt"] = analogRead(PR);
  jsonDoc["ledStatus"] = ledStatus;
  String jsonStr;
  serializeJson(jsonDoc, jsonStr);
  server.send(200, "application/json", jsonStr);
}

void handlePut() {
  String body = server.arg("plain");
  StaticJsonDocument<400> jsonDoc;
  DeserializationError error = deserializeJson(jsonDoc, body);
  if (error) {
    server.send(400, "text/plain", "Invalid JSON");
    return;
  }
  if (jsonDoc.containsKey("speed")) {
    speed = jsonDoc["speed"];
  }
  if (jsonDoc.containsKey("goalpos")) {
    goalpos = jsonDoc["goalpos"];
  }
  server.send(204);
}

void handlePatch() {
  String body = server.arg("plain");
  StaticJsonDocument<400> jsonDoc;
  DeserializationError error = deserializeJson(jsonDoc, body);
  if (error) {
    server.send(400, "text/plain", "Invalid JSON");
    return;
  }
  if (jsonDoc.containsKey("speed")) {
    speed = jsonDoc["speed"];
  }
  if (jsonDoc.containsKey("ledStatus")) {
    ledStatus = jsonDoc["ledStatus"];
  }
  if (jsonDoc.containsKey("goalpos")) {
    goalpos = jsonDoc["goalpos"];
    //
    zCurrent=moveZ(goalpos,speed,zCurrent);
  }
  server.send(204);
  
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  IPAddress staticIP(192, 168, 0, 99 ); // Set desired static IP address here
  IPAddress gateway(192, 168, 0, 1); // Set gateway IP address here
  IPAddress subnet(255, 255, 255, 0); // Set subnet mask here

  WiFi.config(staticIP, gateway, subnet);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/values", HTTP_GET, handleGet);
  server.on("/values", HTTP_PUT, handlePut);
  server.on("/values", HTTP_PATCH, handlePatch);
  server.begin();
}

void loop() {
  server.handleClient();
}
