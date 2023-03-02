jogZ();
int direction = 0;
float speed = 12.5;
float delay = 0;

// read input pin values
up = digitalRead(upPin);
down = digitalRead(downPin);

while (exitJog == LOW)
{
  // need to add code to update speed in mm/s
  delay = 0.05 / speed; // calculate motor cycle delay

  // motor movement loop
  while(up == HIGH || down == HIGH)
  {
    {   
      // set direction of motor
      if(up == HIGH)
      {
        digitalWrite(dirPin, HIGH); // set motor direction up         
      }
      else
      {
        digitalWrite(dirPin, LOW);  // set motor direction down
      }
      
      stepMotor(direction, delay)

      if(up == HIGH)
      {
        zCurrent += 0.1;
      }
      else if (down == HIGH)
      {
        zCurrent -= 0.1;
      }

      // read input pin values
      on = digitalRead(onPin);
    }
  }

  // need to add code to check exitJog status over ethernet
}
