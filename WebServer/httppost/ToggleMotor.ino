// Toggle Motor Driver On/Off (Default On)
bool motorToggle(bool motorStatus) {
  // Relay is normally open, so high is on and low is off
  // checks to see if LED is on/off and reverses value

  if (motorStatus == true) {
    digitalWrite(ledPin, LOW);
    //motorStatus = true;
    Serial.println("Motor: Enabled");
  }
  else {
    digitalWrite(ledPin, HIGH);
    //motorStatus = false;
    Serial.println("Motor: Disabled");
  }

  return motorStatus; // return updated ledStatus
}