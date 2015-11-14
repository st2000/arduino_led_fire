#include "Fire.h" 

#include "Arduino.h"

// Constructor uses passed value to create an instance for that Arduino Uno pin.
Fire::Fire(uint8_t led_pin):private_led_pin(led_pin)
{
	pinMode(private_led_pin, OUTPUT);
}

// Destructor.
Fire::~Fire(){/*nothing to destruct*/}

// Start the fire.
void Fire::begin()
{
	begin(FIRE_NORMAL_FLICKER, FIRE_NORMAL_MIN, FIRE_NORMAL_MAX, FIRE_FIRE);
}

// Start the fire.
void Fire::begin(uint8_t formal_fade_delay)
{
	begin(formal_fade_delay, FIRE_NORMAL_MIN, FIRE_NORMAL_MAX, FIRE_FIRE);
}


void Fire::begin(uint8_t formal_fade_delay, uint16_t formal_fade_min_limit, uint16_t formal_fade_max_limit)
{
	begin(formal_fade_delay, FIRE_NORMAL_MIN, FIRE_NORMAL_MAX, FIRE_FIRE);
}
void Fire::begin(uint8_t formal_fade_delay, uint16_t formal_fade_min_limit, uint16_t formal_fade_max_limit, uint8_t formal_mode)
{
	// Use the unique pin number as the seed for the CRC16 generator. 
	crc = private_led_pin;
	brightness = 128;
	fade_amount = 10;
	fade_direction = true;
	fade_delay = formal_fade_delay;
	fade_min_limit = formal_fade_min_limit;
	fade_max_limit = formal_fade_max_limit;
	fade_mode = formal_mode;
}

// Run the fire algorithm.
void Fire::burn()
{
	fade_amount--;
	if(fade_amount > 0)
	{
		if(fade_direction)
		{
			brightness++;
		}
		else
		{
			brightness--;
		}
		analogWrite(private_led_pin, brightness);
		
		// Pick a minimum brightness limit.
		if (brightness < fade_min_limit)
		{
			fade_direction = true;
		}
		// Pick a maximum brightness limit.
		if (brightness > fade_max_limit)
		{
			fade_direction = false;
		}
	}
	else
	{
		// Only call radom algorithm is mode is fire.  Otherwise
		// assume beacon mode.
		if(fade_mode == FIRE_FIRE)
		{
			algorithm();
		}
	}
}

// Run the fire algorithm.
void Fire::algorithm()
{
	// Exclusive or all feed back bits.
	// Use CRC-16 which is x^16 + x^12 + x^5 + 1 bit positions.
	// (Another common CFC-16 is x^16 + X15 + x^2 + 1.)
	if (0x8000 & crc)
	{
		// Shift all bits left by 1.
		crc <<= 1;
		// Calculate
		if (0x0020 & crc)
		{
			crc &= ~(0x0020);
		}
		else
		{
			crc |= 0x0020;
		}
		
		if (0x1000 & crc)
		{
			crc &= ~(0x1000);
		}
		else
		{
			crc |= 0x1000;
		}
		
		crc |= 0x0001;
	}
	else
	{
		// Shift all bits left by 1.
		crc <<= 1;
		
		if (0x0020 & crc)
		{
			crc |= 0x0020;
		}
		else
		{
			crc &= ~(0x0020);
		}
		
		if (0x1000 & crc)
		{
			crc |= 0x1000;
		}
		else
		{
			crc &= ~(0x1000);
		}
	}
	
	// Randomly change the direction of fading.
	if ((crc & 0xff) > 0x7f)
	{
		fade_direction = !(fade_direction);
	}
	
	// Pick a random number between 3 and 10 to fade to.
	fade_amount = (crc & 0x03) + 7;
	
	// Do not let crc go to zero.
	if (crc == 0)
	{
		crc = 0xffff;
	}
}







