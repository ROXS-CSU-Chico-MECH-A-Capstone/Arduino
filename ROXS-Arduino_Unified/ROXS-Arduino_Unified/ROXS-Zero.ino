zeroZ();
int delay = 4000; // fast movement delay
int slowDelay = 12000; //slow movement delay

// read input pin values
limit = digitalRead(limitPin);

// move motor down until limit switch activation
while(limit == LOW)
{ 
  stepMotor(0,delay)

  limit = digitalRead(limitPin);
}

delay(250);

// move motor vertically offset distance
for (int i = 0; i < offset * zconv; i++)
{
  stepMotor(1,delay)
}

limit = digitalRead(limitPin);

// move motor slowly to zero point
while(limit == LOW)
{ 
  stepMotor(0,slowDelay)

  limit = digitalRead(limitPin);
}