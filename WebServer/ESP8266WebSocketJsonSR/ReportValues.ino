void reportVals(float zCurrent) {
  int intensity = 0;          // voltage as intensity
  intensity = analogRead(A0); // read photoresistor voltage

  String jsonString = "";                           // create a JSON string for sending data to the client
  StaticJsonDocument<200> doc;                      // create JSON container
  JsonObject object = doc.to<JsonObject>();         // create a JSON Object
  object["Intensity"] = intensity;                  // write data into the JSON object -> I used "type" to identify if LED_selected or LED_intensity is sent and "value" for the actual value
  object["CurrentZ"] = zCurrent;
  serializeJson(doc, jsonString);                   // convert JSON object to string
  webSocket.broadcastTXT(jsonString); 
}