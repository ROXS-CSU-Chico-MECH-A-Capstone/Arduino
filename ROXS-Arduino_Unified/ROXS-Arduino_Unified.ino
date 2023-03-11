// Include libraries for JSON and Web Sockets
#include <Ethernet.h>
#include <ArduinoJson.h>
#include <WebSocketServer.h>
using namespace net;

#include <config.h>
#define NETWORK_CONTROLLER ETHERNET_CONTROLLER_W5100
WebSocketServer server{3000};

// assign MAC and IP address for Arduino
byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0x48, 0xD3};
IPAddress ip(192,168,1,200);

constexpr uint16_t port = 3000;
WebSocketServer wss{port};

unsigned int localPort = 8888; // local port to listen on

void jogZ();
void moveZ();
void zeroZ();
void stepMotor();
void reportInt();

//Define digital pins
const int dirPin = 2;         // driver direction control
const int stepPin = 3;        // driver step control
const int downPin = 5;        // driver on/off input
const int upPin = 7;          // driver direction input
const int limitPin = 8;       // z = 0 limit switch
const int runPin = 6;         // run zero function

float zCurrent = 0;

void setup() 
{
  // declare pins as Inputs/Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  pinMode(limitPin, INPUT);
  pinMode(runPin, INPUT);

  Serial.begin(9600);      // start serial port

  // initialize ethernet
  Serial.println(F("Initializing ... "));
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  Serial.print(F("Server running at "));
  Serial.print(Ethernet.localIP());
  Serial.print(F(":"));
  Serial.println(port);
  Ethernet.begin(mac, ip); // start Ethernet

  wss.onConnection([](WebSocket &ws) {
    const auto protocol = ws.getProtocol();
    if (protocol) {
      Serial.print(F("Client protocol: "));
      Serial.println(protocol);
    }

  ws.onMessage([](WebSocket &ws, const WebSocket::DataType dataType,
                  const char *message, uint16_t length) {
    switch (dataType) {
    case WebSocket::DataType::TEXT:
      Serial.print(F("Received: "));
      Serial.println(message);
      break;
    case WebSocket::DataType::BINARY:
      Serial.println(F("Received binary data"));
      break;
    }

    ws.send(dataType, message, length);
  });

  ws.onClose([](WebSocket &, const WebSocket::CloseCode, const char *,
                uint16_t) { Serial.println(F("Disconnected")); });

    Serial.print(F("New client: "));
    Serial.println(ws.getRemoteIP());

    const char message[]{"Hello from Arduino server!"};
    ws.send(WebSocket::DataType::TEXT, message, strlen(message));
  });

  wss.begin();  // start webSocketServer
}

void loop() 
{
  wss.listen();
  //recieve packet

  //example Json
  char json[] = "{\"type\":\"move\",\"zValues\":[100.0,12.5]}";

  StaticJsonDocument<64> cmd;  // initialize Json doc
  DeserializationError error = deserializeJson(cmd, json);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  const char* type = cmd["type"];     // define string from Json doc
  float gotoZ = cmd["zValues"][0];    // define z position float  
  float speed = cmd["zValues"][1];    // define z speed

  // Print values.
  Serial.println(type);
  Serial.println(gotoZ);
  Serial.println(speed);

  if (type == "zero") {
    zCurrent = zeroZ(zCurrent);  //run zeroing function
  }
  else if (type == "move") {
    zCurrent = moveZ(gotoZ, speed, zCurrent);
  }

  reportVals(zCurrent);
}
