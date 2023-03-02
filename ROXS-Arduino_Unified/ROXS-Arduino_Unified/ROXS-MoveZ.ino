moveZ(zCurrent, gotoZ, delay);
{
  for (int i = zCurrent; i < gotoZ)
  {
      digitalWrite(dirPin, HIGH);
    
      // step motor once
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(delay);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(delay);
      
      zCurrent = i;
  }
}