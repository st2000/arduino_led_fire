#include <Lights.h>
#include <Timer.h>

// Assign digital pin 7 & 8 to two red LEDs.
Lights red_ambulance(7,8);
// Assign PWM pin 9 to the yellow LED.
Lights yellow_fire(9);
// Assign PWM pin 10 to the red LED.
Lights red_firetruck(10);
// Assign PWM pin 11 to the gren LED.
Lights green_building(11);


Timer timer;

void setup()
{
	red_ambulance.begin(LIGHTS_FAST_BEACON, LIGHTS_AMBULANCE);
	red_firetruck.begin(LIGHTS_FAST_BEACON, BEACON_MIN, BEACON_MEDIUM, LIGHTS_BEACON);
	green_building.begin(LIGHTS_SLOW_BEACON, BEACON_MIN, BEACON_MAX, LIGHTS_BEACON);
}

void loop()
{
	timer.run();
}
