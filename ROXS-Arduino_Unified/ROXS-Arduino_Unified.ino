// Include libraries for JSON and Web Sockets
#include <ArduinoJson.h>
#include <WebSocketServer.h>
using namespace net;

#include <config.h>
#define NETWORK_CONTROLLER ETHERNET_CONTROLLER_W5100
WebSocketServer server{3000};

void jogZ();
void moveZ();
void zeroZ();
void stepMotor();
void reportInt();

// assign MAC and IP address for Arduino
byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0x48, 0xD3 };
IPAddress ip(192,168,1,200);

constexpr uint16_t port = 3000;
WebSocketServer wss{port};

unsigned int localPort = 8888; // local port to listen on

char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  // buffer to hold incoming packet
char ReplyBuffer[] = "acknowledged";        // a string to send back

//Define digital pins
const int dirPin = 2;         // driver direction control
const int stepPin = 3;        // driver step control
const int downPin = 5;        // driver on/off input
const int upPin = 7;          // driver direction input
const int limitPin = 8;       // z = 0 limit switch
const int runPin = 6;         // run zero function

//Go to Z Parameters
float gotoZ = 0;                // target Z position
float zCurrent = 0;             // current Z position
int exitJog = 0;

float speed = 12.5;             //default speed


const int capacity = JSON_OBJECT_SIZE(3) + 2*JSON_OBJECT_SIZE(1); StaticJsonDocument<capacity> doc;

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

  // initialize thernet
  Serial.println(F("Initializing ... "));

  // Ethernet.init(10);
  Ethernet.init(53); // Mega2560
  // Ethernet.init(5); // ESPDUINO-32
  // Ethernet.init(PA4); // STM32

  Ethernet.begin(mac, ip); // initialize 

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

  wss.begin();  // start webSocketServer


}

void loop() 
{
  wss.listen();

  //example Json
  char json[] = "{\"type\":\"move\",\"zValues\":[100.0,12.5]}";
  StaticJsonDocument<64> cmd;  // initialize Json doc
  DeserializationError error = deserializeJson(cmd, json);

  const char* type = doc["type"]; // define string from Json doc
  gotoZ = doc["zValues"][0];      // define z position float  
  speed = doc["zValues"][1];      // define z speed

  // Print values.
  Serial.println(type);
  Serial.println(gotoZ);
  Serial.println(speed);

  if (type == "zero")
  {
    zeroZ(zCurrent);  //run zeroing function
  }
  else if (type == "move")
  {
    moveZ(gotoZ, speed, zCurrent);
  }
  else if (type == "jog")
  {
    jogZ(zCurrent);
  }
}
