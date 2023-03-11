// Include libraries for JSON and Web Sockets
#include <Arduino_JSON.h>

#include <WebSocket.h>
#include <WebSocketClient.h>
#include <WebSocketServer.h>
#include <config.h>
#include <platform.h>
#include <utility.h>

WebSocketServer server{3000};

void jogZ();
void moveZ();
void zeroZ();
void stepMotor();
void reportInt();

// assign MAC and IP address for Arduino
byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0x48, 0xD3 };
IPAddress ip(192,168,1,200);

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

int speed = 12.5;             //default speed

String readString = "";
String zeroString = "zero";
String moveString = "move";
String jogString = "jog";
String exitString = "exit";

void setup() 
{
  Ethernet.begin(mac, ip); // start Ethernet

  server.onConnection([](WebSocket &ws) {
    const char message[]{ "Hello from Arduino server!" };
    ws.send(WebSocket::DataType::TEXT, message, strlen(message));

    ws.onClose([](WebSocket &ws, const WebSocket::CloseCode code,
                 const char *reason, uint16_t length) {
      // ...
    });
    ws.onMessage([](WebSocket &ws, const WebSocket::DataType dataType,
                   const char *message, uint16_t length) {
      // ...
    });
  });

  server.begin();          //start Websocket Server

  // open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only

  // declare pins as Inputs/Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  pinMode(limitPin, INPUT);
  pinMode(runPin, INPUT);
  }

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
}

void loop() 
{
  server.listen();
  // serial Monitoring
  // if there's data available, read a packet
  char json[] =
      "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, json);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  // Fetch values.
  //
  // Most of the time, you can rely on the implicit casts.
  // In other case, you can do doc["time"].as<long>();
  const char* sensor = doc["sensor"];
  long time = doc["time"];
  double latitude = doc["data"][0];
  double longitude = doc["data"][1];

  // Print values.
  Serial.println(sensor);
  Serial.println(time);
  Serial.println(latitude, 6);
  Serial.println(longitude, 6);

  if (readString == "zeroString")
  {
    zeroZ(zCurrent);  //run zeroing function
  }
  else if (readString == "moveString")
  {
    moveZ(zCurrent, gotoZ, speed);
  }
  else if (readString == "jogString")
  {
    jogZ(zCurrent);
  }
}
