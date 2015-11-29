#ifndef Lights_H
#define Lights_H
	
#include <inttypes.h>

// Here are some brightness level suggestions.
#define LIGHTS_DIMMER_MIN 1
#define LIGHTS_NORMAL_MIN 20
#define LIGHTS_BRIGHER_MIN 50
#define LIGHTS_DIMMIER_MAX 100
#define LIGHTS_NORMAL_MAX 200
#define LIGHTS_BRIGHTER_MAX 254
#define BEACON_MIN 10
#define BEACON_MEDIUM 40
#define BEACON_MAX 80
// Here are some flicker speed suggestions.
// (Only delay on the first LED.  Otherwise
//  each additional LED burn() call will cause
//  a delay.)
#define LIGHTS_FAST_FLICKER 5
#define LIGHTS_NORMAL_FLICKER 10
#define LIGHTS_SLOW_FLICKER 20
#define LIGHTS_FAST_BEACON 5
#define LIGHTS_SLOW_BEACON 20
// Here are two pattern modes.  For
// fire and for beacon.
enum
{
	LIGHTS_FIRE = 0,
	LIGHTS_BEACON,
	LIGHTS_AMBULANCE,
};
		
class Lights 
{
	public:
	
	Lights(uint8_t led_pin);
	Lights(uint8_t led_pin_00, uint8_t led_pin_01);
	~Lights();
	void begin();
	void begin(uint8_t);
	void begin(uint8_t, uint16_t, uint16_t);
	void begin(uint8_t, uint16_t, uint16_t, uint8_t);
	static void call_into_lights(void *);
	void burn();
	void begin(uint8_t, uint8_t);
	static void call_into_flash(void *);
	void flash();
	
	private:
	
	void algorithm();
	uint8_t private_led_pin;	
	uint8_t private_led_pin_00;	
	uint8_t private_led_pin_01;	
	uint16_t crc;
	uint8_t brightness;
	int8_t fade_amount;
	bool fade_direction;
	uint8_t fade_loop;
	uint8_t fade_delay;
	uint16_t fade_min_limit;
	uint16_t fade_max_limit;
	uint8_t fade_mode;
};

#endif
