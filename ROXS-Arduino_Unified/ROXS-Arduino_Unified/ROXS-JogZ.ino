jogZ(zConv, zCurrent, delay);

// read input pin values
on = digitalRead(onPin);
dir = digitalRead(dircontrolPin);

while (exitJog == LOW)
{
  // motor movement loop
  while(on == HIGH)
  {
    {   
      dir = digitalRead(dircontrolPin);

      // set direction of motor
      if(dir == HIGH)
      {
        digitalWrite(dirPin, HIGH); // set motor direction up         
      }
      else
      {
        digitalWrite(dirPin, LOW);  // set motor direction down
      }
      
      // step motor once
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(400);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(400);

      if(dir == HIGH)
      {
        zCurrent += 1/zConv;
      }
      else
      {
        zCurrent += 1/zConv;
      }

      // read input pin values
      on = digitalRead(onPin);
    }
  }
}
