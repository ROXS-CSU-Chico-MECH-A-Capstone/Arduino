
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

//const char* ssid = "MPJAC82";
//const char*password= "N0t14u2c.82";
const char* ssid = "ROXS24";
const char*password= "capstone";

// create prototypes for functions
void moveZ();
float zeroZ();
float stepMotor();
bool ledToggle();
//void handleGetPR();


// Initial constant paramters
float zCurrent = 0;   // in mm
bool ledStatus = false; // false = off, true = on
int speed = 0;
float goalpos = 0;
float goalposLED = 0; //distance from LED emiter to zero of the gantry in mm
int zero = 0;
float LEDZeroOffset = 563.0; //distance from LED emiter to zero of the gantry in mm
float GRange =463.001;

// Define pinouts for digital in/out & analog read

//const int stepPin = 13;     // to step pin on motor driver
//const int dirPin = 12;      // to direction pin on motor driver
//const int limitPin = 5;   // from limit switch input
//const int ledPin = 4;     // to relay for LED


const int stepPin = 5;     // to step pin on motor driver
const int dirPin = 4;      // to direction pin on motor driver
const int limitPin = 13;   // from limit switch input
const int enable = 14;   //
const int ledPin = 12;     // to relay for LED

const int PR = A0;   // from photoresistor circuit

ESP8266WebServer server(80);



//________________Handle get requests for data______________________________________________
void handleGet() {
  StaticJsonDocument<400> jsonDoc;
  jsonDoc["speed"] = speed;
  jsonDoc["goalpos"] = goalpos;
  jsonDoc["zCurrent"] = zCurrent;
  jsonDoc["zCurrentLED"] = zCurrent;
  jsonDoc["goalposLED"] = goalposLED;
  jsonDoc["PRInt"] = analogRead(PR);
  jsonDoc["ledStatus"] = ledStatus;
  jsonDoc["zero"] = zero;
  String jsonStr;
  serializeJson(jsonDoc, jsonStr);
  server.send(200, "application/json", jsonStr);
}


//___________Handle patch requests for data updates and calling functions________________________________________________
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
  
  if (jsonDoc.containsKey("goalpos")) {//Move command with zero as datum
    goalpos = jsonDoc["goalpos"];
    //
    if (goalpos < GRange){
      zCurrent=moveZ(goalpos,speed,zCurrent);
    } else{
    Serial.print("Attempted Goal Position of");
    Serial.print(goalpos);
    Serial.print("Exceeds Gantry Range of");
    Serial.print(GRange);
    Serial.println("");
  }}
  
  if (jsonDoc.containsKey("goalposLED")) {//Move command with emitter as datum
    goalposLED = jsonDoc["goalposLED"];
    //goal position in positive offset from LED

    goalpos=LEDZeroOffset-goalposLED;
    
    if (goalpos < GRange){
      zCurrent=moveZ(goalpos,speed,zCurrent);
    }   
      else{
    Serial.print("Attempted Goal Position of");
    Serial.print(goalpos);
    Serial.print("Exceeds Gantry Range of");
    Serial.print(GRange);
    Serial.println("");
  }}
    if (jsonDoc.containsKey("ledStatus")) {
    ledStatus = jsonDoc["ledStatus"];
    ledStatus=ledToggle(ledStatus);
  }
  
  if (jsonDoc.containsKey("zero")) {
    zero = jsonDoc["zero"];
    zCurrent=zeroZ(zCurrent);
  }

  
  server.send(204);
}

void setup() {

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(limitPin, INPUT);
  
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
  server.on("/values", HTTP_PATCH, handlePatch);
  server.begin();
}

void loop() {
  server.handleClient();
 
}
