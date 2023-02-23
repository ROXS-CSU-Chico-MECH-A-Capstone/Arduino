//Load Arduino Libraries
#include <SPI.h>
#include <Ethernet.h>

//Assign MAC and IP address for Arduino
byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0x48, 0xD3 };
IPAddress ip(192,168,1,200);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255, 255, 255, 0);

EthernetServer server(8081);
String readString;

//Define digital pins
const int dirPin = 2;         //driver direction control
const int stepPin = 3;        //driver step control
const int onPin = 5;          //driver on/off input
const int dircontrolPin = 7;  //driver direction input
const int limitPin = 8;       //z = 0 limit switch
const int runPin = 6;         //run zero function

//Gantry Parameters
int dir = 0;     //direction status
int on = 0;      //on/off status
int limit = 0;   //motor limit status
int runZero = 0; //Manually activate zero function
int hasRun = 0;  //if function has been run already = 0;

//Go to Z Parameters
int gotoZ = 0;                         //Target Z position
int zCurrent = 0;                      //Current Z position

int exitJog;

//Lead Screw Scaling Calculations
const int pitch = 2;                     //mm per rev
const int res = 200;                     //steps per rev (full step) 
int zConv = res / pitch;                 //steps per mm
int speed = 0;                           //movement speed in mm per sec
float delay = pitch / (2 * res * speed); //delay calc
const float zeroSpeed 12.5;              //zero procedure gantry speed in mm per sec
int zeroDelay = pitch / (2 * res * zeroSpeed);

void setup() 
{
  //Declare pins as Inputs/Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(onPin, INPUT);
  pinMode(dircontrolPin, INPUT);
  pinMode(limitPin, INPUT);
  pinMode(runPin, INPUT);

  Serial.begin(9600);

  //start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());
  Serial.println("ROXS Photodetector Measure & Control");
}

void loop() 
{
/*
  zeroZ(zeroDelay);
  moveZ(zCurrent, gotoZ, delay);
  jogZ(zConv, zCurrent, delay);
*/
}
