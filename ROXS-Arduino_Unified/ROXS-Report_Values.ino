void reportVals(float zCurrent) {
  int intensity = 0;        // voltage as intensity
  intensity = analogRead(A0); // read photoresistor voltage

  // convert intensity to string
  char charVal[10];            
  dtostrf(intensity, 2, 1, charVal);

  // serialize Json packet with intensity and zCurrent
  // send packet with websocket
}