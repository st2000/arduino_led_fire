#ifndef Time_H
#define Time_H

#include <inttypes.h>
#include <StandardCplusplus.h>
#include <vector>
#include <iterator>
	
typedef void (*timer_callback)(void *);

class Time
{
	public:
	
	Time(){};
	~Time(){};
	void speed(uint16_t delay_ms, timer_callback function_name, void * inst);
	void run();
	
	private:
	
	struct callback_info
	{
		uint16_t callback_delay;
		timer_callback callback;
		uint16_t time_last_called;
		void * inst;
		uint16_t time_old;
	};
	std::vector<callback_info> callbackData;
};

#endif
