void reportInt()
{
  int intensity = 0;        // voltage as intensity
  intensity = analogRead(A0); // read photoresistor voltage

  // convert intensity to string
  char charVal[10];            
  dtostrf(intensity, 2, 1, charVal);

  // send packet with intensity value
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Udp.write(charVal);
  Udp.endPacket();
}