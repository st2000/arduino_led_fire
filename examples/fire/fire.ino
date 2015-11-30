#include <Lights.h>
#include <Timer.h>

// Assign PWM pin 9 to the yellow LED.
Lights yellow_fire(9);

Timer timer;

void setup()
{
	yellow_fire.begin();
}

void loop()
{
	timer.run();
}
