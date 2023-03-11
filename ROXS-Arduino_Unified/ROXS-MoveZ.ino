float moveZ(float gotoZ, float speed, float zCurrent)
{
  // zCurrent is the current known z position of gantry
  // gotoZ is the desired z postion

  float disp = abs(gotoZ - zCurrent);
  float delay = 0.05 / speed * 1000000; // speed in mm/s to delay in microsecs
  
  // initialize direction pin output
  int dir  = 0;
  
  if (gotoZ != zCurrent)
  {
    // set gantry direction
    if (gotoZ > zCurrent)
    {
      dir = 1;
    }  
    
    for (int i = 0; i < disp; i++)
    { 
      stepMotor(dir, delay, zCurrent);
    }
  }
  return zCurrent;
}
