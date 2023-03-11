void stepMotor(int direction, float delay, int zCurrent){
  // direction = 0 or 1
  // delay determines speed
  
  // set direction of motor
  if (direction == 0){
    digitalWrite(dirPin, LOW);
    zCurrent -= 0.1; // mm
  }
  else {
    digitalWrite(dirPin, HIGH);
    zCurrent += 0.1; // mm
  }
  
  // step motor once
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(delay);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(delay);

  //temporarily holds data from vals
  char charVal[10];            
  dtostrf(zCurrent, 2, 1, charVal);

  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Udp.write(charVal);
  Udp.endPacket();
}
