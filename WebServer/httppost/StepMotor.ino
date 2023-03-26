// Step motor once in (Direction Up/Down) with (Delay) between impulses
float stepMotor(int direction, float delay, float zCurrent) {
  // direction = 0 or 1
  // delay determines speed
  
  // set direction of motor
  if (direction == 0) {
    digitalWrite(dirPin, LOW);
    Serial.print(zCurrent);
    Serial.print(" - ");
    zCurrent -= 0.1; // mm
    Serial.print(zCurrent);
    Serial.print("\n");
  }
  else {
    digitalWrite(dirPin, HIGH);
    Serial.print(zCurrent);
    zCurrent += 0.1; // mm
    Serial.print(zCurrent);
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
