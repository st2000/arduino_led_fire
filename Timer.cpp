#include "Timer.h" 
#include "Arduino.h"

void Timer::speed(uint16_t delay_ms, timer_callback function_name, void * formal_inst) 
{
	callback_delay[timer_count] = delay_ms;
	callbacks[timer_count] = function_name;
	time_last_called[timer_count] = millis() & 0xffff;
	inst[timer_count] = formal_inst;
	timer_count++;
}

void Timer::run()
{
	uint8_t i;
	uint16_t time_now;
	uint16_t time_delta;

	time_now = 0xffff & millis();

	// If a ms has not changed skip this routine.
	if(time_now != time_old)
	{
		// Check to see if time_now cycled through zero.
		if(time_now > time_old)
		{
			time_delta = time_now - time_old;
		}
		else
		{
			time_delta = 0xffff - (time_old - time_now);
		}
		time_old = time_now;

		// Cycle through all the registered callbacks.
		for(i = 0; i < timer_count; i++)
		{
			if(callback_delay[i] < (time_delta + time_last_called[i]))
			{
				time_last_called[i] = 0;
				// Make the call back.
				(*(callbacks[i]))(inst[i]);
			}
			else
			{
				time_last_called[i] += time_delta;
			}
		}
	}
}


