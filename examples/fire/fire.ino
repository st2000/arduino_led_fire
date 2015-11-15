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
	
	time.speed((uint16_t)8, fire_red.get_fire_pt, &fire_red); 
	time.speed((uint16_t)5, fire_green.get_fire_pt, &fire_green); 
	
	Serial.begin(9600);
}

void loop()
{
	time.run();
}
