/*
 *  Simple hello world Json REST response
  *  by Mischianti Renzo <https://www.mischianti.org>
 *
 *  https://www.mischianti.org/
 *
 */
 
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>                              // needed for JSON encapsulation (send multiple variables with one string)

 
//const char* ssid = "WhatsBetterThan25";
//const char* password = "welding26";
const char* ssid = "ROXS24";
const char*password= "capstone";
//const char* ssid = "ARRIS-F125";
//const char* password = "5G5344102373";

int photoresistorPin = A0;

ESP8266WebServer server(80);
 
// Serving Hello world
void getHelloWord() {
    server.send(200, "text/json", "{\"name\": \"Hello world\"}");
}

// Serving Photoresistor Value
void getPRValue() {
    String msg= String(analogRead(photoresistorPin));
    server.send(200, "text/json", msg);
    //some other functionality goes here
}

void setspeed() {
  int spee = 105;                   //arbitrary placeholder
  String spvalue = "Speed is " + String(spee);
  server.send(200, "text/json", spvalue);
}

void goalposition() {
  int gpos = 100;                   //arbitrary placeholder
  String gposvalue = "Goal position is " + String(gpos);
  server.send(200, "text/json", gposvalue);
}

void PRandCurrentPos(){
  /*StaticJsonBuffer<200> jsonBuffer;
  // Build your own object tree in memory to store the data you want to send in the request
  JsonObject& Posandprdata = jsonBuffer.createObject();
  Posandprdata.set("Intensity", instensity);
  Posandprdata.set("CurrentZ", zCurrent);*/

  int intensity = analogRead(A0); // read photoresistor voltage
  int zCurrent = 6;                 //arbitrary just for testing
  String values = "";
  StaticJsonDocument<64> doc;
  doc["Intensity"] = intensity;
  doc["CurrentZ"] = zCurrent;
  /*serializeJson(doc, values);
  
  // deserialize the object
  char json[] = "{\"hello\":\"world\"}";
  deserializeJson(doc, json);
  // extract the data
  JsonObject object = doc.as<JsonObject>();*/
  String PRandCPos = "Current postion is " + String(doc["CurrentZ"]) + " Current Intensity is " + String(doc["Intensity"]);
  server.send(200, "text/json", PRandCPos);
}
// Define routing
void restServerRouting() {
    server.on("/", HTTP_GET, []() {
        server.send(200, F("text/html"),
            F("Welcome to the REST ESP8266 Web Server based on http protocol"));
    });
    //Put different http adresses here
    server.on(F("/helloWorld"), HTTP_GET, getHelloWord);
    server.on(F("/getPRValue"), HTTP_GET, getPRValue);
    server.on(F("/setspeed"), HTTP_GET, setspeed);
    server.on(F("/goalposition"), HTTP_GET, goalposition);
    server.on(F("/PRandCPos"), HTTP_GET, PRandCurrentPos);
}
 
// Manage not found URL
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
 
void setup(void) {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  // Activate mDNS this is used to be able to connect to the server
  // with local DNS hostmane esp8266.local
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
 
  // Set server routing
  restServerRouting();
  // Set not found response
  server.onNotFound(handleNotFound);
  // Start server
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void) {
  server.handleClient();
}
