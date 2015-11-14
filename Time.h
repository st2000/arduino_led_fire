#ifndef Time_H
#define Time_H

#include <inttypes.h>
	
typedef void (*timer_callback)(void);
	
class Time
{
	public:
	
	Time();
	~Time();
	
	void speed(uint16_t delay_ms, timer_callback function_name);
	void run();
	
	private:
	uint8_t timer_count;
	
	uint8_t callback_delay[10];
    timer_callback callbacks[10];
    uint16_t time_last_called[10];
};

#endif
