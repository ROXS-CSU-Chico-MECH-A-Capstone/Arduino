stepMotor(int direction, float delay)
// direction = 0 or 1
// delay determines speed

// set direction of motor
if (direction == 0)
{
  digtalWrite(dirPin, LOW);
}
else
{
  digitalWrite(dirPin, HIGH);
}

// step motor once
digitalWrite(stepPin, HIGH);
delayMicroseconds(delay);
digitalWrite(stepPin, LOW);
delayMicroseconds(delay);