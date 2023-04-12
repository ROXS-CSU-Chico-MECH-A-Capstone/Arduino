// Zero photoresistor gantry with limit switch
float zeroZ(float zCurrent)
{
  // report zeroing routine to serial
  Serial.println("Running Zeroing Routine...");

  int delay = 500;      // fast movement delay (12.5mm/s)
  int slowDelay = 12000; // slow movement delay (4.17mm/s)
  int offset = 1 * 100;  // vertical offset distance (40mm)
  
  // read input pin values
  int limit = digitalRead(limitPin);
  
  // move motor down until limit switch activation
  while(limit == LOW) { 
    zCurrent = stepMotor(0, delay, zCurrent);
  
    limit = digitalRead(limitPin);
    Serial.println("Running Zero");
    Serial.println(limit);
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
    Serial.println("Running Zero");
    Serial.println(limit);
  }
  
  zCurrent = 0;
  //reportVals(zCurrent);

  // report zeroing routine to serial
  Serial.println("Zeroing Routine Complete");
  Serial.println("New Gantry Position = +0.00mm");

  return zCurrent; // return updated z value
}
