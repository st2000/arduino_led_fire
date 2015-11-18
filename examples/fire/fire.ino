#include <Fire.h>
#include <Time.h>

// Assign pin 9 to the yellow LED.
Fire fire_yellow(9);
// Assign pin 10 to the red LED.
Fire fire_red(10);
// Assign pin 10 to the gren LED.
Fire fire_green(11);

//Time time;

void setup()
{
	fire_yellow.begin();
	fire_red.begin(FIRE_FAST_BEACON, BEACON_MIN, BEACON_MAX, FIRE_BEACON);
	fire_green.begin(FIRE_SLOW_BEACON, BEACON_MIN, BEACON_MAX, FIRE_BEACON);
}

void loop()
{
//	time.run();
	fire_yellow.run();
}
