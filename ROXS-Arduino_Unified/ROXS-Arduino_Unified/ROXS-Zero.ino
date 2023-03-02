zeroZ(float zCurrent);
int delay = 4000;      // fast movement delay
int slowDelay = 12000; // slow movement delay
int offset = 4 * 100;  // vertical offset distance

// read input pin values
int limit = digitalRead(limitPin);

// move motor down until limit switch activation
while(limit == LOW)
{ 
  stepMotor(0, delay, zCurrent)

  limit = digitalRead(limitPin);
}

delay(250);

// move motor vertically offset distance
for (int i = 0; i < offset; i++)
{
  stepMotor(1, delay, zCurrent);
}

limit = digitalRead(limitPin);

// move motor slowly to zero point
while(limit == LOW)
{ 
  stepMotor(0, slowDelay, zCurrent)

  limit = digitalRead(limitPin);
}

// report current z value
ss1 << zCurrent
std::string zReport = ss1.str()
Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
Udp.write(zReport);
Udp.endPacket();