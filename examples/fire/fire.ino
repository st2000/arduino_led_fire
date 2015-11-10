#include <Fire.h>

// Assign pin 9 to the red LED.
Fire fire_red(9);
// Assign pin 10 to the gren LED.
Fire fire_green(10);

void setup()
{
  /*nothing to setup*/
}

void loop()
{
  fire_red.begin();
  fire_green.begin(FIRE_NO_DELAY, FIRE_DIMMER_MIN, FIRE_BRIGHTER_MAX);
  
  for(;;)
  {
    fire_red.burn();
    fire_green.burn();
  }
}


