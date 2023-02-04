// Define pin connections and file variables
const int onPin = 5;         //stepping on/off input pin
const int dircontrolPin = 7; //dirction input pin

const int dirPin = 2;   //direction output pin
const int stepPin = 3;  //stepping on/off output pin

int dir = 0; //direction status
int on = 0;  //on/off status

void setup()
{
  //Declare pins as Inputs/Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(onPin, INPUT);
  pinMode(dircontrolPin, INPUT);
}

void loop()
{
  //read input pin values
  on = digitalRead(onPin);
  dir = digitalRead(dircontrolPin);

  //motor movement loop
  while(on == HIGH)
  {
    {   
      //set direction of motor
      if(dir == HIGH)
      {
        digitalWrite(dirPin, HIGH); //set motor direction up         
      }
      else
      {
        digitalWrite(dirPin, LOW);  //set motor direction down
      }
      
      //step motor once
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(400);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(400);

      //read input pin values
      dir = digitalRead(dircontrolPin);
      on = digitalRead(onPin);
    }
  }       
}
