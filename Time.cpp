#include "Time.h" 
#include "Arduino.h"

// Constructor.
Time::Time(){}

// Destructor.
Time::~Time(){/*nothing to destruct*/}

void Time::speed(uint16_t delay_ms, timer_callback function_name) 
{
	callback_info info;
	info.callback_delay = delay_ms;
	info.callback = function_name;
	info.time_last_called = millis();
	callbackData.push_back(info);
}

void Time::run()
{
	uint16_t time_now;
	std::vector<callback_info>::iterator it;
	
	time_now = millis();

	for(it = callbackData.begin(); it != callbackData.end(); it++)
	{
		if((it->time_last_called + it->callback_delay) < time_now)
		{
			it->time_last_called += it->callback_delay;
			(*(it->callback))();
		}
	}
}







