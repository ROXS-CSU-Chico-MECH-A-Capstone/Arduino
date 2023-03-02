moveZ(float zCurrent, float gotoZ, float speed);
// zCurrent is the current known z position of gantry
// gotoZ is the desired z postion

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

  for (int i = zCurrent; i < gotoZ)
  { 
    stepMotor(dir, delay, zCurrent)
    if (dir == 0)
    {
      i -= 1;
    }
    else if (dir == 1)
    {
      i += 1;
    }
  }
}