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
const int downPin = 5;        // driver on/off input
const int upPin = 7;          // driver direction input
const int limitPin = 8;       // z = 0 limit switch
const int runPin = 6;         // run zero function

//Go to Z Parameters
int gotoZ = 0;                // target Z position
int zCurrent = 0;             // current Z position

int exitJog = 0;

char readString;
zeroString = String("zero");
moveString = String("move");
jogString = String("jog");
exitString = String("exit");

void stepMotor(int direction, float delay, float zCurrent);
void moveZ(float zCurrent, float gotoZ, float speed);
void zeroZ(float zCurrent);
void jogZ(int zCurrent);

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

  if (readString == "zeroString")
  {
    zeroZ(zeroDelay);  //run zeroing function
  }
  else if (readString == "moveString")
  {
    //check for z coordinate
    moveZ(zCurrent, gotoZ, delay);
  }
  }
  else if (readString == "jogString")
  {
    jogZ(zConv, zCurrent, delay);
  }
}

void stepMotor(int direction, float delay, float zCurrent){
// direction = 0 or 1
// delay determines speed

// set direction of motor
if (direction == 0)
{
  digtalWrite(dirPin, LOW);
  zCurrent -= 0.1; // mm
}
else
{
  digitalWrite(dirPin, HIGH);
  zCurrent += 0.1; // mm
}

// step motor once
digitalWrite(stepPin, HIGH);
delayMicroseconds(delay);
digitalWrite(stepPin, LOW);
delayMicroseconds(delay);

// report current z value
ss1 << zCurrent
std::string zReport = ss1.str()
Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
Udp.write(zReport);
Udp.endPacket();
}

void moveZ(float zCurrent, float gotoZ, float speed){
// zCurrent is the current known z position of gantry
// gotoZ is the desired z postion

float delay = 0.05 / speed * 1000000; // speed in mm/s to delay in microsecs

// initialize direction pin output
int dir  = 0;

if (gotoZ != zCurrent)
{
  // set gantry direction
  if (gotoZ > zCurrent)
  {
    dir = 1;
  }

  for (int i = zCurrent; i < gotoZ)
  { 
    stepMotor(dir, delay, zCurrent)
    if (dir == 0)
    {
      i -= 1;
    }
    else if (dir == 1)
    {
      i += 1;
    }
  }
}
}

void zeroZ(float zCurrent){
int delay = 4000;      // fast movement delay
int slowDelay = 12000; // slow movement delay
int offset = 4 * 100;  // vertical offset distance

// read input pin values
int limit = digitalRead(limitPin);

// move motor down until limit switch activation
while(limit == LOW)
{ 
  stepMotor(0, delay, zCurrent)

  limit = digitalRead(limitPin);
}

delay(250);

// move motor vertically offset distance
for (int i = 0; i < offset; i++)
{
  stepMotor(1, delay, zCurrent);
}

limit = digitalRead(limitPin);

// move motor slowly to zero point
while(limit == LOW)
{ 
  stepMotor(0, slowDelay, zCurrent)

  limit = digitalRead(limitPin);
}

// report current z value
ss1 << zCurrent
std::string zReport = ss1.str()
Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
Udp.write(zReport);
Udp.endPacket();
}

void jogZ(int zCurrent){
float speed = 12.5; // mm/s
float delay = 0;    // microsecs
int dir = 0;

// read input pin values
up = digitalRead(upPin);
down = digitalRead(downPin);

while (exitJog == LOW)
{
  // need to add code to update speed in mm/s
  delay = 0.05 / speed; // calculate motor cycle delay

  // motor movement loop
  while(up == HIGH || down == HIGH)
  {
    {   
      // set dir of motor
      if(up == HIGH)
      {
        dir = 1;
        digitalWrite(dirPin, HIGH); // set motor direction up         
      }
      else
      {
        dir = 0;
        digitalWrite(dirPin, LOW);  // set motor direction down
      }
      
      stepMotor(dir, delay, zCurrent)

      if(up == HIGH)
      {
        zCurrent += 0.1; // mm
      }
      else if (down == HIGH)
      {
        zCurrent -= 0.1; // mm
      }

      // read input pin values
      on = digitalRead(onPin);
    }
  }

  // need to add code to check exitJog status over ethernet
}
}
