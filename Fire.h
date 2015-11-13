#ifndef Fire_H
#define Fire_H
	
#include <inttypes.h>

// Here are some brightness level suggestions.
#define FIRE_DIMMER_MIN 1
#define FIRE_NORMAL_MIN 20
#define FIRE_BRIGHER_MIN 50
#define FIRE_DIMMIER_MAX 100
#define FIRE_NORMAL_MAX 200
#define FIRE_BRIGHTER_MAX 254
#define BEACON_MIN 10
#define BEACON_MAX 80
// Here are some flicker speed suggestions.
// (Only delay on the first LED.  Otherwise
//  each additional LED burn() call will cause
//  a delay.)
#define FIRE_NO_DELAY 0
#define FIRE_FAST_FLICKER 2
#define FIRE_NORMAL_FLICKER 4
#define FIRE_SLOW_FLICKER 6
// Here are two pattern modes.  For
// fire and for beacon.
#define FIRE_FIRE 0
#define FIRE_BEACON 1
	
typedef void (*timer_callback)(void);
	
class Fire 
{
	public:
	
	Fire(uint8_t led_pin);
	~Fire();
	void begin();
	void begin(uint8_t);
	void begin(uint8_t, uint16_t, uint16_t);
	void begin(uint8_t, uint16_t, uint16_t, uint8_t);
	void burn();
	
	void speed(uint16_t delay_ms, timer_callback function_name);
	void run();
	
	private:
	
	void algorithm();
	uint8_t private_led_pin;	
	uint16_t crc;
	uint8_t brightness;
	uint8_t fade_amount;
	bool fade_direction;
	uint8_t fade_loop;
	uint8_t fade_delay;
	uint16_t fade_min_limit;
	uint16_t fade_max_limit;
	uint8_t fade_mode;
	uint8_t timer_count;
	
	uint8_t callback_delay[10];
    timer_callback callbacks[10];
    uint16_t time_last_called[10];

};
	
#endif
