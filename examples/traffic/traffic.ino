#include <Lights.h>
#include <Timer.h>


// Assigning pins 11, 9 & 10 to green, yellow and red traffic lights.
// We can have traffic lights for one direction like in this next commented out line of code.
// Lights traffic_lights(11, 9, 10);
// Assigning pins 11, 9 & 10 to green, yellow and red east-west traffic lights and pins
// 4, 5 & 6 for green, yellow and red north-south traffic lights.
// We can have traffic lights for both directions like in this next line of code.
Lights traffic_lights(11, 9, 10, 4, 5, 6);

Timer timer;

void setup()
{
	traffic_lights.begin(LIGHTS_NORMAL_TRAFFIC, LIGHTS_TRAFFIC);
}

void loop()
{
	timer.run();
}
