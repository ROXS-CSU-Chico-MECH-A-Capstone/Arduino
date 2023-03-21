// Toggle LED On/Off (Default Off)
bool ledToggle(bool ledStatus) {
  // Relay is normally open, so high is on and low is off
  // checks to see if LED is on/off and reverses value

  if (ledStatus == false) {
    digitalWrite(ledPin, HIGH);
    ledStatus = true;
    Serial.println("LED: On");
  }
  else {
    digitalWrite(ledPin, LOW);
    ledStatus = false;
    Serial.println("LED: Off");
  }

  return ledStatus; // return updated ledStatus
}