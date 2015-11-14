#include <Fire.h>
#include <Time.h>

// Assign pin 9 to the red LED.
Fire fire_red(9);
// Assign pin 10 to the gren LED.
Fire fire_green(10);

Time time;

void setup()
{
  fire_red.begin();
  fire_green.begin(FIRE_NORMAL_FLICKER, BEACON_MIN, BEACON_MAX, FIRE_BEACON);

  time.speed((uint16_t)4, doit);
  time.speed((uint16_t)5, doitto); 
}

void loop()
{
   time.run();
}

void doit()
{
  fire_red.burn();
}

void doitto()
{
  fire_green.burn();
}
