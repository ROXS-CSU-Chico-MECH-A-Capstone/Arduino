// Move photoresistor gantry to (Position) at (Speed)
float moveZ(float gotoZ, float speed, float zCurrent){
  // zCurrent is the current known z position of gantry
  // gotoZ is the desired z postion

  float disp = abs(gotoZ - zCurrent);
  float delay = 0.05 / speed * 1000000; // speed in mm/s to delay in microsecs
  
  // initialize direction pin output
  int dir  = 0;
  
  if (gotoZ != zCurrent) {
    // set gantry direction up/down
    if (gotoZ > zCurrent) {
      dir = 1;  // change to up if target > current position
    }   
    for (int i = 0; i < disp; i++) { 
      stepMotor(dir, delay, zCurrent);
    }
  }

  // Report new gantry position to serial
  String newZ = "";
  newZ.concat(zCurrent);
  Serial.print("New Gantry Position: +");
  Serial.print(newZ);
  Serial.println("mm");

  return zCurrent; // return updated z value
}