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
// Here are some flicker speed suggestions.
// (Only delay on the first LED.  Otherwise
//  each additional LED burn() call will cause
//  a delay.)
#define FIRE_NO_DELAY 0
#define FIRE_FAST_FLICKER 2
#define FIRE_NORMAL_FLICKER 4
#define FIRE_SLOW_FLICKER 6
	
class Fire 
{
	public:
	
	Fire(uint8_t led_pin);
	~Fire();
	void begin();
	void begin(uint8_t);
	void begin(uint8_t, uint16_t, uint16_t);
	void burn();
	
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
};
	
#endif
