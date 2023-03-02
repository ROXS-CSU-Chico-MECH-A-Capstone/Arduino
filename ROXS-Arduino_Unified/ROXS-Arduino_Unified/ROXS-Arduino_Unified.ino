//Load Arduino Libraries
#include <Ethernet.h>
#include <EthernetUdp.h>

// assign MAC and IP address for Arduino
byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0x48, 0xD3 };
IPAddress ip(192,168,1,200);

unsigned int localPort = 8888; // local port to listen on

char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  // buffer to hold incoming packet
char ReplyBuffer[] = "acknowledged";        // a string to send back

EthernetUDP Udp;

//Define digital pins
const int dirPin = 2;         // driver direction control
const int stepPin = 3;        // driver step control
const int downPin = 5;          // driver on/off input
const int upPin = 7;  // driver direction input
const int limitPin = 8;       // z = 0 limit switch
const int runPin = 6;         // run zero function

//Go to Z Parameters
int gotoZ = 0;                         // target Z position
int zCurrent = 0;                      // current Z position

int exitJog = 0;

char readString;
zeroString = String("zero");
moveString = String("move");
jogString = String("jog");
exitString = String("exit");

void setup() 
{
  // declare pins as Inputs/Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(onPin, INPUT);
  pinMode(dircontrolPin, INPUT);
  pinMode(limitPin, INPUT);
  pinMode(runPin, INPUT);

  // start the Ethernet
  Ethernet.begin(mac, ip);

  // open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
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

  // start UDP
  Udp.begin(localPort);
}

void loop() 
{
  // serial Monitoring
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) 
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    for (int i=0; i < 4; i++) 
    {
      Serial.print(remote[i], DEC);
      if (i < 3) 
      {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    readstring = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.println(packetBuffer);

    // send a reply to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }

  if (readString == zeroString)
  {
    zeroZ(zeroDelay);  //run zeroing function
  }
  else if (readString == moveString)
  {
    //check for z coordinate
    moveZ(zCurrent, gotoZ, delay);
  }
  }
  else if (readString == jogString)
  {
    jogZ(zConv, zCurrent, delay);
  }
}