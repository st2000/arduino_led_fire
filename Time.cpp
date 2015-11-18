#include "Time.h" 
#include "Arduino.h"

void Time::speed(uint16_t delay_ms, timer_callback function_name, void * inst) 
{
	callback_info info;
	info.callback_delay = delay_ms;
	info.callback = function_name;
	info.time_last_called = millis();
	info.inst = inst;
	callbackData.push_back(info);
}

void Time::run()
{
	uint16_t time_now;
	std::vector<callback_info>::iterator it;
	uint16_t time_next_call;

	time_now = 0xffff & millis();

	for(it = callbackData.begin(); it != callbackData.end(); it++)
	{
		time_next_call = 0xffff & (it->time_last_called + it->callback_delay);
	
		if(time_now < it->time_old)
		{
			// Assume timer wrapped so reset last time called.
			it->time_last_called = time_now;
		}
		it->time_old = time_now;

		if(time_next_call < time_now)
		{
			if(time_now > (time_next_call + it->callback_delay))
			{
				// Don't fall too far behind.
				it->time_last_called = (0x0ffff & time_now);
			}
			else
			{
				it->time_last_called = time_next_call;
			}
			// Call the burn method in the correct instance of the Fire class.
			(*(it->callback))(it->inst);
		}
	}
}

