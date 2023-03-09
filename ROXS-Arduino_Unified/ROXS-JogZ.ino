void jogZ(float zCurrent)
{
  float speed = 12.5; // mm/s
  float delay = 0;    // microsecs
  int dir = 0;
  int up = 0;
  int down = 0;
  
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
        // incriment current z value (mm)
        if(up == HIGH)
        {
          dir = 1;
          zCurrent += 0.1; 
        }
        else if (down == HIGH)
        {
          dir = 0;
          zCurrent -= 0.1;
        }

        stepMotor(dir, delay, zCurrent);
  
        // read input pin values
        up = digitalRead(upPin);
        down = digitalRead(downPin);
      }
    }
  
    // need to add code to check exitJog status over ethernet
  }
}
