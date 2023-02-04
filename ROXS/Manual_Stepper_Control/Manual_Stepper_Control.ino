// Define pin connections & motor's steps per revolution
const int dirPin = 2;
const int stepPin = 3;

const int onPin = 5;
const int dircontrolPin = 7;

const int stepsPerRevolution = 20000;
int dir = 0;
int on = 0;

void setup()
{
  // Declare pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(onPin, INPUT);
  pinMode(dircontrolPin, INPUT);
}
void loop()
{
  // Spin motor quickly
  digitalWrite(dirPin, HIGH);
  on = digitalRead(onPin);
  dir = digitalRead(dircontrolPin);
  s
        while(on == HIGH)
        {
          {   
            if(dir == HIGH)
            {
              digitalWrite(dirPin, HIGH);           
            }
            else
            {
              digitalWrite(dirPin, LOW);
            }
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(400);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(400);
              dir = digitalRead(dircontrolPin);
              on = digitalRead(onPin);
          }
        }       

}
