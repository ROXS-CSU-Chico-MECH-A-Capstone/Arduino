// Zero photoresistor gantry with limit switch
float zeroZ(float zCurrent)
{
  // report zeroing routine to serial
  Serial.println("Running Zeroing Routine...");

  int delay = 4000;      // fast movement delay (12.5mm/s)
  int slowDelay = 12000; // slow movement delay (4.17mm/s)
  int offset = 4 * 100;  // vertical offset distance (4mm)
  
  // read input pin values
  int limit = digitalRead(limitPin);
  
  // move motor down until limit switch activation
  while(limit == LOW) { 
    zCurrent = stepMotor(0, delay, zCurrent);
  
    limit = digitalRead(limitPin);
  }

  delayMicroseconds(250);
  
  // move motor vertically offset distance
  for (int i = 0; i < offset; i++) {
    zCurrent = stepMotor(1, delay, zCurrent);
  }
  
  limit = digitalRead(limitPin);
  
  // move motor slowly to zero point
  while(limit == LOW) { 
    zCurrent = stepMotor(0, slowDelay, zCurrent);
  
    limit = digitalRead(limitPin);
  }
  
  zCurrent = 0;
  reportVals(zCurrent);

  // report zeroing routine to serial
  Serial.println("Zeroing Routine Complete");

  return zCurrent; // return updated z value
}