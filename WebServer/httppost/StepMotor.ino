// Step motor once in (Direction Up/Down) with (Delay) between impulses
float stepMotor(int direction, float delay, float zCurrent) {
  // direction = 0 or 1
  // delay determines speed
  // set direction of motor
  if (direction == 0) {
    digitalWrite(dirPin, LOW);
    Serial.println(" - ");
    zCurrent -= 0.04; // mm
  }
  else {
    digitalWrite(dirPin, HIGH);
    Serial.println(" + ");
    zCurrent += 0.04; // mm
  }
   
  // step motor once
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(delay);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(delay);

  //reportVals(zCurrent);
  handleGet();
  return zCurrent; // return updated z value
}
