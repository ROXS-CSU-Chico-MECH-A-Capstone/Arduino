void reportInt()
{
  int intensity = 0;        // voltage as intensity
  intensity = analogRead(A0); // read photoresistor voltage

  //temporarily holds data from vals
  char charVal[intensity];                

  //4 is mininum width, 3 is precision; float value is copied onto buff
  dtostrf(123.234, 4, 3, charVal);

  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Udp.write(charVal);
  Udp.endPacket();
}