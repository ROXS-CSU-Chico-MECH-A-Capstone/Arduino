void handleGetPR() {
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["value"] = analogRead(photoresistorPin);
  String jsonStr;
  serializeJson(jsonDoc, jsonStr);
  server.send(200, "application/json", jsonStr);
}
