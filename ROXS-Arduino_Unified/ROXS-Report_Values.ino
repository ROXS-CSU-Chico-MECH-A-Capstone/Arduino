void reportVals(float zCurrent) {
  int intensity = 0;          // voltage as intensity
  intensity = analogRead(A0); // read photoresistor voltage

  String values = "";
  StaticJsonDocument<64> doc;
  doc["Intensity"] = intensity;
  doc["CurrentZ"] = zCurrent;
  serializeJson(doc, values);
  // serialize Json packet with intensity and zCurrent
  // send packet with websocket
}