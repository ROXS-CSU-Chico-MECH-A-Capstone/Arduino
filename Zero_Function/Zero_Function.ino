//Find zero point on z gantry

//Define pin connections and file variables
const int dirPin = 2;         //driver direction control
const int stepPin = 3;        //driver step control
const int onPin = 5;          //driver on/off input
const int dircontrolPin = 7;  //driver direction input
const int limitPin = 8;       //z = 0 limit switch
const int runPin = 6;         //run zero function

int dir = 0;     //direction status
int on = 0;      //on/off status
int limit = 0;   //limit switch status
int runZero = 0; //run zero function
int hasRun = 0;  //if function has been run already = 0;


const int zconv = 200/8;  //steps/rev per mm pitch
int offset = 3;           //offset movement in mm
int zmax = 463;           //final height

void setup() 
{
  //Declare pins as Inputs/Outputs
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(onPin, INPUT);
  pinMode(dircontrolPin, INPUT);
  pinMode(limitPin, INPUT);
  pinMode(runPin, INPUT);
}

void loop() 
{
  runZero = digitalRead(runPin);
  hasRun = 0;

  while (runZero == 0)
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
    runZero = digitalRead(runPin);
  }

  limit = digitalRead(limitPin); //check limit switch status

  while(hasRun = 0)
  {
    //move motor down until limit switch activation
    while(limit == LOW)
    { 
      digitalWrite(dirPin, LOW);
      
      //step motor once
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(400);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(400);

      limit = digitalRead(limitPin);
    }
  
    delay(250);

    //move motor vertically offset distance
    for (int i = 0; i < offset * zconv; i++)
    {
      digitalWrite(dirPin, HIGH);
    
      //step motor once
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(400);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(400);
    }

    limit = digitalRead(limitPin);

    //move motor slowly to zero point
    while(limit == LOW)
    { 
      digitalWrite(dirPin, LOW);
      
      //step motor once
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(4000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(4000);

      limit = digitalRead(limitPin);
    }

    delay(1000);

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
    hasRun = 1;
  }
}
