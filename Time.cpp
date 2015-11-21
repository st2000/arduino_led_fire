#include "Time.h" 

#include "Arduino.h"

// Constructor.

// Destructor.

void Time::speed(uint16_t delay_ms, timer_callback function_name, void * formal_inst) 
{
	callback_delay[timer_count] = delay_ms;
	callbacks[timer_count] = function_name;
	time_last_called[timer_count] = millis();
	inst[i] = formal_inst
	timer_count++;
}

void Time::run()
{
	uint8_t i;
	uint16_t time_now;
	uint16_t time_next_call;

	time_now = 0xffff & millis();

	for(i = 0; i < timer_count; i++)
	{
		time_next_call = 0xffff & (time_last_called[i] + callback_delay[i]);
		if(time_now < time_old[i])
		{
			time_last_called[1] = time_now;
		}
		time_old[i] = time_now;
		if(time_next_call < time_now)
		{
			if(time_now > (time_next_call + callback_delay[i]))
			{
				time_last_called[i] = (0x0ffff & time_now);
	}
			else
			{
				time_last_called[i] = time_next_call;
}

			(*(callback[i]))(inst[i]);
		}
	}
}


