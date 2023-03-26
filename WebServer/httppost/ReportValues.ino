// Report current Z value and photoresistor intensity over websocket server
void reportVals() {
  
  
  int intensity = 0;           // voltage as intensity
  intensity = analogRead(A0);  // read photoresistor voltage (0-1V on ESP8266)

  String jsonString = "";                    // create a JSON string for sending data to the client
  StaticJsonDocument<200> doc;               // create JSON container
  JsonObject object = doc.to<JsonObject>();  // create a JSON Object
  object["Intensity"] = intensity;           // write intensity into JSON object
  object["CurrentZ"] = zCurrent;             // write current Z value into JSON object
  serializeJson(doc, jsonString);            // convert JSON object to string
  server.send(200, "application/json", jsonString);
}
