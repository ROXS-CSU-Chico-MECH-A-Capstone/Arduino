//Define pin connections
const int stepPin = 3;

void setup() 
{
  pinMode(stepPin, OUTPUT);
}

void loop()
{
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(400);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(400);
}
