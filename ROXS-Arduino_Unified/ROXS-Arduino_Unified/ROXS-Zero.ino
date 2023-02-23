zeroZ(zeroDelay);

const int slowFactor = 4;

//read input pin values
limit = digitalRead(limitPin);

//move motor down until limit switch activation
while(limit == LOW)
{ 
  digitalWrite(dirPin, LOW);
  
  //step motor once
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(zeroDelay);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(zeroDelay);

  limit = digitalRead(limitPin);
}

delay(250);

//move motor vertically offset distance
for (int i = 0; i < offset * zconv; i++)
{
  digitalWrite(dirPin, HIGH);

  //step motor once
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(zeroDelay);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(zeroDelay);
}

limit = digitalRead(limitPin);

//move motor slowly to zero point
while(limit == LOW)
{ 
  digitalWrite(dirPin, LOW);
  
  //step motor once
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(zeroDelay*slowFactor);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(zeroDelay*slowFactor);

  limit = digitalRead(limitPin);
}

delay(1000);
/*
//move motor vertically to zmax
for (int i = 0; i < zmax * zconv; i++)
{
  digitalWrite(dirPin, HIGH);

  //step motor once
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(400);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(400);
}
*/