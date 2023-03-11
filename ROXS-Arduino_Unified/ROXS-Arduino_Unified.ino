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

void moveZ();
float zeroZ();
float stepMotor();
void reportVals();

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
  Serial.print(F("Initializing Ethernet... "));
  Ethernet.begin(mac, ip);
  Serial.println("Ready");

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
    Serial.println("Ethernet shield found.");
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected... ");
    while (true) {
      delay(1);      
    }
    Serial.println("Ethernet cable connected.");
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

  StaticJsonDocument<64> doc;  // initialize Json doc
  DeserializationError error = deserializeJson(doc, json);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  const char* type = doc["type"];     // define string from Json doc
  float gotoZ = doc["zValues"][0];    // define z position float  
  float speed = doc["zValues"][1];    // define z speed

  // Print values.
  Serial.print("A command of type: ");
  Serial.print(type);
  Serial.print(" was recieved.");

  if (type == "zero") {
    zCurrent = zeroZ(zCurrent);  //run zeroing function
  }
  else if (type == "move") {
    Serial.print("Target Z: ");
    Serial.println(gotoZ);
    Serial.print("Speed: ");
    Serial.println(speed);
    zCurrent = moveZ(gotoZ, speed, zCurrent);
  }

  reportVals(zCurrent);
}
