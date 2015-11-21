#include <Lights.h>
#include <Timer.h>

// Assign pin 9 to the yellow LED.
Lights fire_yellow(9);
// Assign pin 10 to the red LED.
Lights beacon_red(10);
// Assign pin 10 to the gren LED.
Lights beacon_green(11);

Timer timer;

void setup()
{
	fire_yellow.begin();
	beacon_red.begin(LIGHTS_FAST_BEACON, BEACON_MIN, BEACON_MEDIUM, LIGHTS_BEACON);
	beacon_green.begin(LIGHTS_SLOW_BEACON, BEACON_MIN, BEACON_MAX, LIGHTS_BEACON);
}

void loop()
{
	timer.run();
}
