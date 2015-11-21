#ifndef Timer_H
#define Timer_H

#include <inttypes.h>
	
typedef void (*timer_callback)(void *);
	
class Timer
{
	public:
	
	Timer(){};
	~Timer(){};
	
	void speed(uint16_t delay_ms, timer_callback function_name, void * formal_inst);
	void run();
	
	private:
	uint8_t timer_count = 0;
	
	uint16_t callback_delay[10];
    timer_callback callbacks[10];
    uint16_t time_last_called[10];
	void * inst[10];
	uint16_t time_old;
};

#endif
