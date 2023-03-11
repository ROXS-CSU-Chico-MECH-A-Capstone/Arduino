bool ledToggle(bool ledStatus) {
  // checks to see if LED is on/off and reverses value
  if (ledStatus == false) {
    digitalWrite(ledPin, HIGH);
    ledStatus = true;
    Serial.println("LED: On");
  }
  else{
    digitalWrite(ledPin, LOW);
    ledStatus = false;
    Serial.println("LED: Off");
  }
  return ledStatus;
}