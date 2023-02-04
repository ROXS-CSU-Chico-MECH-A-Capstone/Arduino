//Define pin connections and file variables
const int limitPin = 8;
const int dirPin = 2;
const int stepPin = 3;

int dir = 0; //direction status
int on = 0;  //on/off status
int limit = 0; //motor limit status
int offset = 512; //offset movement in steps

void setup() 
{
  //Declare pins as Inputs/Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(onPin, INPUT);
  pinMode(dircontrolPin, INPUT);
  pinMode(limitPin, INPUT);
}

void loop() 
{
  //read input pin values
  on = digitalRead(onPin);
  dir = digitalRead(dircontrolPin);
  limit = digitalRead(limitPin);

  //motor movement loop
  while(limit == LOW)
  { 
    digitalWrite(dirPin = HIGH);
      
    //step motor once
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(400);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(400);

    limit = digitalRead(limitPin);
  }

  for (int i = 0; i < offset; i++)
  {
    digitalWrite(dirpin = LOW);
    
    //step motor once
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(400);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(400);
  }

  while(limit == LOW)
  { 
    digitalWrite(dirPin = HIGH);
      
    //step motor once
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(5000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(5000);

    limit = digitalRead(limitPin);
  }
}
