jogZ(int zCurrent);
float speed = 12.5; // mm/s
float delay = 0;    // microsecs
int dir = 0;

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
      // set dir of motor
      if(up == HIGH)
      {
        dir = 1;
        digitalWrite(dirPin, HIGH); // set motor direction up         
      }
      else
      {
        dir = 0;
        digitalWrite(dirPin, LOW);  // set motor direction down
      }
      
      stepMotor(dir, delay, zCurrent)

      if(up == HIGH)
      {
        zCurrent += 0.1; // mm
      }
      else if (down == HIGH)
      {
        zCurrent -= 0.1; // mm
      }

      // read input pin values
      on = digitalRead(onPin);
    }
  }

  // need to add code to check exitJog status over ethernet
}
