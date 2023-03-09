void stepMotor(int direction, float delay, int zCurrent)
{
  // direction = 0 or 1
  // delay determines speed
  
  // set direction of motor
  if (direction == 0)
  {
    digitalWrite(dirPin, LOW);
    zCurrent -= 0.1; // mm
  }
  else
  {
    digitalWrite(dirPin, HIGH);
    zCurrent += 0.1; // mm
  }
  
  // step motor once
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(delay);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(delay);

  //temporarily holds data from vals
  char charVal[zCurrent];            

  //4 is mininum width, 3 is precision; float value is copied onto buff
  dtostrf(123.234, 4, 3, charVal);

  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Udp.write(charVal);
  Udp.endPacket();
}
