stepMotor(int direction, float delay, float zCurrent)
// direction = 0 or 1
// delay determines speed

// set direction of motor
if (direction == 0)
{
  digtalWrite(dirPin, LOW);
  zCurrent -= 0.1; // mm
}
else
{
  digitalWrite(dirPin, HIGH);
  zCurrent += 0.1; // mm
}

// step motor once
digitalWrite(stepPin, HIGH);
delayMicroseconds(delay);
digitalWrite(stepPin, LOW);
delayMicroseconds(delay);

// report current z value
ss1 << zCurrent
std::string zReport = ss1.str()
Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
Udp.write(zReport);
Udp.endPacket();