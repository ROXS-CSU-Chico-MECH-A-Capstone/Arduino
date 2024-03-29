// ---------------------------------------------------------------------------------------
//
// Code for a simple webserver on the ESP8266
// The code opens inputs for position and speed with submit buttons and uses Websockets to continuously
// update the web-clients. For data transfer JSON encapsulation is used.
//
// For installation, the following libraries need to be installed:
// * ESP8266WiFi
// * ESP8266WebServer
// * Websockets by Markus Sattler (can be tricky to find -> search for "Arduino Websockets"
// * ArduinoJson by Benoit Blanchon
//
// NOTE: in principle this code is universal and can be used on Arduino AVR as well. However, AVR is only supported with version 1.3 of the webSocketsServer. Also, the Websocket
// library will require quite a bit of memory, so wont load on Arduino UNO for instance. The ESP32 and ESP8266 are cheap and powerful, so use of this platform is recommended. 
//
// Refer to https://youtu.be/15X0WvGaVg8
//
// Written by mo thunderz (last update: 27.08.2022)
// Adapted by Jeremy West
// ---------------------------------------------------------------------------------------

#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>
#include <ESP8266WiFi.h>                                     // needed to connect to WiFi
#include <ESP8266WebServer.h>                                // needed to create a simple webserver (make sure tools -> board is set to ESP32, otherwise you will get a "WebServer.h: No such file or directory" error)
#include <WebSocketsServer.h>                         // needed for instant communication between client and server through Websockets
#include <ArduinoJson.h>                              // needed for JSON encapsulation (send multiple variables with one string)

// SSID and password of Wifi connection:
//const char* ssid = "WhatsBetterThan25";
//const char* password = "welding26";
//const char* ssid = "MPJAC82";
//const char*password= "N0t14u2c.82";
const char* ssid = "ROXS24";
 const char*password= "capstone";

// Initial constant paramters
float speed=1;
float pos=1;


#define NUM_LEDS  23
#define LED_PIN   D2
CRGB leds[NUM_LEDS];

// The String below "webpage" contains the complete HTML code that is sent to the client whenever someone connects to the webserver
String  webpage = "<!DOCTYPE html><html> <head> <title>ESP8266 WifiServer</title> </head> <body> <h1>ESP8266 WifiServer</h1><p><h2>Input Position</h2></p> <div> <span> <input type='number' id='pos' placeholder='Enter Position' name='Name' maxlength='4'/> <input type='number' id='speed' placeholder='Enter Speed' name='Name' maxlength='4'/> </span> </div> <div> <input type='submit' id='submit1' value='Update Position'> <input type='submit' id='submit2' value='Update Speed'> <input type='submit' id='submit3' value='Home'> </div> <div> <label for='output1'>Called Position</label> <p class='output' id='output1'></p> <label for='output2'>Called Speed</label> <p class='output' id='output2'></p> </div> </body> <script> document.getElementById('submit1').addEventListener('click', UpdatePos); document.getElementById('submit2').addEventListener('click', UpdateSpeed); document.getElementById('submit3').addEventListener('click', Home); var out1 = document.getElementById('output1'); var out2 = document.getElementById('output2'); var pos = document.getElementById('pos'); var speed = document.getElementById('speed'); var Socket; function init() { Socket = new WebSocket('ws://' + window.location.hostname + ':81/'); Socket.onmessage = function(event) { processCommand(event); }; } function UpdatePos () { var l_pos= pos.value; out1.innerHTML =l_pos; console.log(l_pos); var msg = { type: 'New Pos', value: l_pos}; Socket.send(JSON.stringify(msg)); } function UpdateSpeed () { var l_speed= speed.value; out2.innerHTML =l_speed; console.log(l_speed); var msg = { type: 'New Speed', value: l_speed}; Socket.send(JSON.stringify(msg)); } function Home () { console.log('Home called'); var msg = { type: 'Home'}; Socket.send(JSON.stringify(msg)); } function processCommand(event) { var obj = JSON.parse(event.data); var type = obj.type; if (type.localeCompare('New Pos') == 0) { var l_pos = parseInt(obj.value); console.log(l_pos); out1.innerHTML = l_pos; } else if (type.localeCompare('New Speed') == 0) { var l_speed = parseInt(obj.value); console.log(l_speed); out2.innerHTML = l_speed; } document.getElementById('pos').innerHTML = obj.pos; document.getElementById('speed').innerHTML = obj.speed; console.log(obj.pos); console.log(obj.speed); } window.onload = function(event) { init(); } </script></html>";

// The JSON library uses static memory, so this will need to be allocated:
// -> in the video I used global variables for "doc_tx" and "doc_rx", however, I now changed this in the code to local variables instead "doc" -> Arduino documentation recomends to use local containers instead of global to prevent data corruption

// We want to periodically send values to the clients, so we need to define an "interval" and remember the last time we sent data to the client (with "previousMillis")
int interval = 1000;                                  // send data to the client every 1000ms -> 1s
unsigned long previousMillis = 0;                     // we use the "millis()" command for time reference and this will output an unsigned long

// Initialization of webserver and websocket
ESP8266WebServer server(80);                                 // the server uses port 80 (standard port for websites
WebSocketsServer webSocket = WebSocketsServer(81);    // the websocket uses port 81 (standard port for websockets

void setup() {
  Serial.begin(9600);                               // init serial port for debugging
  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  
  WiFi.begin(ssid, password);                         // start WiFi interface
  Serial.println("Establishing connection to WiFi with SSID: " + String(ssid));     // print SSID to the serial interface for debugging
 
  while (WiFi.status() != WL_CONNECTED) {             // wait until WiFi is connected
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");  
  Serial.print("Connected to network with IP address: ");
  Serial.println(WiFi.localIP());                     // show IP address that the ESP8266 has received from router
  
  server.on("/", []() {                               // define here what the webserver needs to do
    server.send(200, "text/html", webpage);           //    -> it needs to send out the HTML string "webpage" to the client
  });

  server.begin();                                     // start server
  webSocket.begin();                                  // start websocket
  webSocket.onEvent(webSocketEvent);                  // define a callback function -> what does the ESP32 need to do when an event from the websocket is received? -> run function "webSocketEvent()"
  Serial.print("System Nominal");
  Serial.print("");
}

void loop() {
  server.handleClient();                              // Needed for the webserver to handle all clients
  webSocket.loop();                                   // Update function for the webSockets 
}

void webSocketEvent(byte num, WStype_t type, uint8_t * payload, size_t length) {      // the parameters of this callback function are always the same -> num: id of the client who send the event, type: type of message, payload: actual data sent and length: length of payload
  Serial.print("Websocket Event Detected");
  switch (type) {                                     // switch on the type of information sent
    case WStype_DISCONNECTED:                         // if a client is disconnected, then type == WStype_DISCONNECTED
      Serial.println("Client " + String(num) + " disconnected");
      break;
    case WStype_CONNECTED:                            // if a client is connected, then type == WStype_CONNECTED
      Serial.println("Client " + String(num) + " connected");
      // optionally you can add code here what to do when connected
      break;
    case WStype_TEXT:                                 // if a client has sent data, then type == WStype_TEXT
      // try to decipher the JSON string received
      StaticJsonDocument<200> doc;                    // create a JSON container
      DeserializationError error = deserializeJson(doc, payload);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }
      else {
        // JSON string was received correctly, so information can be retrieved:
        const char* l_type = doc["type"];
        const char* l_value = doc["value"];
        Serial.println("Type: " + String(l_type));
        Serial.println("Value: " + String(l_value));

        // if "New Speed" is received -> update speed constant
        if(String(l_type) == "New Speed") {
          speed = int(l_value);

          Red();
          FastLED.show();
          sendJson("New Speed", String(l_value));
          //function goes here
          
          
        }
        
        // if "New Pos" is received -> update Pos and call move function
        if(String(l_type) == "New Pos") {
          pos = int(l_value);
          sendJson("New Pos", String(l_value));
          //function goes here
          Blue();
          FastLED.show();

        }

         // if "Home" is received -> call Home function
        if(String(l_type) == "Home") {
          //function goes here
          Gradient();
          FastLED.show();
        }
      }
      Serial.println("");
      break;
  }
}


void Red(){
  Serial.println("Red");
  Serial.println("");
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
}

void Blue(){
  Serial.println("Blue");
  Serial.println("");
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
}

void Gradient(){
  Serial.println("Gradient");
  Serial.println("");
  fill_gradient_RGB(leds, NUM_LEDS, CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Magenta);
  FastLED.show();
}

void Rainbow(){
  Serial.println("Rainbow");
  Serial.println("");
  fill_rainbow(leds, NUM_LEDS, 0, speed / NUM_LEDS);
  FastLED.show();
}

//Update all clients with other client's activities
//Send Json back to ESP8266 for everyone else to see
void sendJson(String l_type, String l_value) {
    String jsonString = "";                           // create a JSON string for sending data to the client
    StaticJsonDocument<200> doc;                      // create JSON container
    JsonObject object = doc.to<JsonObject>();         // create a JSON Object
    object["type"] = l_type;                          // write data into the JSON object -> I used "type" to identify if LED_selected or LED_intensity is sent and "value" for the actual value
    object["value"] = l_value;
    serializeJson(doc, jsonString);                // convert JSON object to string
    webSocket.broadcastTXT(jsonString);               // send JSON string to all clients
} 
  
  
