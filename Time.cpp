#include "Time.h" 

#include "Arduino.h"

// Constructor.
Time::Time(){}

// Destructor.
Time::~Time(){/*nothing to destruct*/}

void Time::speed(uint16_t delay_ms, timer_callback function_name) 
{
	callback_delay[timer_count] = delay_ms;
	callbacks[timer_count] = function_name;
	time_last_called[timer_count] = millis();
	timer_count++;
}

void Time::run()
{
	uint8_t i;
	uint16_t time_now;

	time_now = millis();

	for (i = 0; i < timer_count; i++) 
	{
		if (time_now - time_last_called[i] >= callback_delay[i]) 
		{
			time_last_called[i] += callback_delay[i];
			(*callbacks[i])();
		}
	}
}







