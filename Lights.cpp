#include "Lights.h" 
#include "Timer.h"
#include "Arduino.h"

extern Timer timer;

// Constructor uses passed value to create an instance for that Arduino Uno pin.
Lights::Lights(uint8_t led_pin):private_led_pin_00(led_pin)
{
	pinMode(private_led_pin_00, OUTPUT);
}

// Constructor uses passed value to create an instance for that Arduino Uno pin.
Lights::Lights(uint8_t led_pin_00, uint8_t led_pin_01):private_led_pin_00(led_pin_00), private_led_pin_01(led_pin_01)
{
	pinMode(private_led_pin_00, OUTPUT);
	pinMode(private_led_pin_01, OUTPUT);
}

// Constructor uses passed value to create an instance for that Arduino Uno pin.
Lights::Lights(uint8_t led_pin_00, uint8_t led_pin_01, uint8_t led_pin_02):
private_led_pin_00(led_pin_00), private_led_pin_01(led_pin_01), private_led_pin_02(led_pin_02)
{
	pinMode(private_led_pin_00, OUTPUT);
	pinMode(private_led_pin_01, OUTPUT);
	pinMode(private_led_pin_02, OUTPUT);
	mode_traffic_full = false;
	fade_direction = false;
	brightness = 1;
}

// Constructor uses passed value to create an instance for that Arduino Uno pin.
Lights::Lights(uint8_t led_pin_00, uint8_t led_pin_01, uint8_t led_pin_02, uint8_t led_pin_03, uint8_t led_pin_04, uint8_t led_pin_05):
private_led_pin_00(led_pin_00), private_led_pin_01(led_pin_01), private_led_pin_02(led_pin_02), private_led_pin_03(led_pin_03), private_led_pin_04(led_pin_04), private_led_pin_05(led_pin_05)
{
	pinMode(private_led_pin_00, OUTPUT);
	pinMode(private_led_pin_01, OUTPUT);
	pinMode(private_led_pin_02, OUTPUT);
	pinMode(private_led_pin_03, OUTPUT);
	pinMode(private_led_pin_04, OUTPUT);
	pinMode(private_led_pin_05, OUTPUT);
	mode_traffic_full = true;
	fade_direction = false;
	brightness = 1;
}

// Destructor.
Lights::~Lights(){/*nothing to destruct*/}

// Start fire or beacon light show.
void Lights::begin()
{
	begin(LIGHTS_FAST_FLICKER, LIGHTS_NORMAL_MIN, LIGHTS_NORMAL_MAX, LIGHTS_FIRE);
}

// Start fire or beacon light show.
void Lights::begin(uint8_t formal_fade_delay)
{
	begin(formal_fade_delay, LIGHTS_NORMAL_MIN, LIGHTS_NORMAL_MAX, LIGHTS_FIRE);
}

// Start fire or beacon light show.
void Lights::begin(uint8_t formal_fade_delay, uint16_t formal_fade_min_limit, uint16_t formal_fade_max_limit)
{
	begin(formal_fade_delay, LIGHTS_NORMAL_MIN, LIGHTS_NORMAL_MAX, LIGHTS_FIRE);
}

// Start fire or beacon light show.
void Lights::begin(uint8_t formal_fade_delay, uint16_t formal_fade_min_limit, uint16_t formal_fade_max_limit, uint8_t formal_mode)
{
	// Use the unique pin number as the seed for the CRC16 generator. 
	crc = private_led_pin_00;
	brightness = 128;
	fade_amount = 10;
	fade_direction = true;
	fade_delay = formal_fade_delay;
	fade_min_limit = formal_fade_min_limit;
	fade_max_limit = formal_fade_max_limit;
	fade_mode = formal_mode;
	
	timer.speed((uint16_t)fade_delay, this->call_into_lights, this); 
}

// Start flash ambulance or traffic-lights light show.
void Lights::begin(uint8_t formal_fade_delay, uint8_t formal_mode)
{
	if(formal_mode == LIGHTS_AMBULANCE)
	{
		fade_delay = formal_fade_delay;
		timer.speed((uint16_t)fade_delay, this->call_into_flash, this); 
	}
	else
	{
		if(formal_mode == LIGHTS_TRAFFIC)
		{
			fade_delay = formal_fade_delay;
			timer.speed((uint16_t)fade_delay, this->call_into_traffic, this); 
		}
	}
}

// Run the fire and / or beacon algorithm.
void Lights::burn()
{
	// Only call radom algorithm if mode is fire.  Otherwise
	// assume beacon mode.
	if(fade_mode == LIGHTS_FIRE)
	{
		fade_amount--;
	}
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
		analogWrite(private_led_pin_00, brightness);
		
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
		algorithm();
	}
}


// Run the fire & beacon algorithm.
void Lights::algorithm()
{
	// Exclusive or all feed back bits.
	// Use CRC-16 which is x^16 + x^12 + x^5 + 1 bit positions.
	// (Another common CFC-16 is x^16 + X15 + x^2 + 1.)
	if (0x8000 & crc)
	{
		// Shift all bits left by 1.
		crc <<= 1;
		
		// Calculate
		crc ^= 0x1020;		
		crc |= 0x0001;
	}
	else
	{
		// Shift all bits left by 1.
		crc <<= 1;
	}
	
	// Randomly change the direction of fading about half the time.
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


// Run the flash algorithm.
void Lights::flash()
{
	if(fade_direction)
	{
		brightness++;
	}
	else
	{
		brightness--;
	}
	
	if(fade_direction)
	{
		if(
				((brightness > 40) && (brightness < 50)) ||
				((brightness > 70) && (brightness < 80)) ||
				((brightness > 90) && (brightness < 100))
				)
		{
			digitalWrite(private_led_pin_00, HIGH);
		}
		else
		{
			digitalWrite(private_led_pin_00, LOW);
		}
	}
	else
	{
		if(
				((brightness > 40) && (brightness < 50)) ||
				((brightness > 70) && (brightness < 80)) ||
				((brightness > 90) && (brightness < 100))
				)
		{
			digitalWrite(private_led_pin_01, HIGH);
		}
		else
		{
			digitalWrite(private_led_pin_01, LOW);
		}
	}
	
	// Switch direction at limit.
	if (brightness == 0)
	{
		fade_direction = true;
	}
	else
	{
		if (brightness >= 0x7f)
		{
			fade_direction = false;
		}
	}
}


// Run the traffic algorithm.
void Lights::traffic()
{
	if(fade_direction)
	{
		brightness++;
	}
	else
	{
		brightness--;
	}
	
	if(fade_direction)
	{
		if(brightness == 0)
		{
			redYellowGreen(private_led_pin_00);
			if(mode_traffic_full)
			{
				redYellowGreen(private_led_pin_05);
			}
		}
		else
		{
			if(brightness == 80)
			{
				redYellowGreen(private_led_pin_01);
			}
			else
			{
				if(brightness == 100)
				{
					redYellowGreen(private_led_pin_02);
					if(mode_traffic_full)
					{
						redYellowGreen(private_led_pin_03);
					}
				}
			}
		}
	}
	else
	{
		if(brightness == 100)
		{
			redYellowGreen(private_led_pin_02);
			if(mode_traffic_full)
			{
				redYellowGreen(private_led_pin_03);
			}
		}
		else
		{
			if(brightness == 20)
			{
				if(mode_traffic_full)
				{
					redYellowGreen(private_led_pin_04);
				}
			}
			else
			{
				if(brightness == 0)
				{
					redYellowGreen(private_led_pin_00);
					if(mode_traffic_full)
					{
						redYellowGreen(private_led_pin_05);
					}
				}
			}
		}
	}
	
	// Switch direction at limit.
	if (brightness == 0)
	{
		fade_direction = true;
	}
	else
	{
		if (brightness >= 100)
		{
			fade_direction = false;
		}
	}
}

void Lights::redYellowGreen(uint8_t formal_pin)
{
	// Then only turn on the 1 LED passed to us.
	if(formal_pin == private_led_pin_00)
	{
		digitalWrite(private_led_pin_00, HIGH);
		digitalWrite(private_led_pin_01, LOW);
		digitalWrite(private_led_pin_02, LOW);
	}
	else
	{
		if(formal_pin == private_led_pin_01)
		{
			digitalWrite(private_led_pin_00, LOW);
			digitalWrite(private_led_pin_01, HIGH);
			digitalWrite(private_led_pin_02, LOW);
		}
		else
		{
			if(formal_pin == private_led_pin_02)
			{
				digitalWrite(private_led_pin_00, LOW);
				digitalWrite(private_led_pin_01, LOW);
				digitalWrite(private_led_pin_02, HIGH);
			}
		}
	}

	if(formal_pin == private_led_pin_03)
	{
		digitalWrite(private_led_pin_03, HIGH);
		digitalWrite(private_led_pin_04, LOW);
		digitalWrite(private_led_pin_05, LOW);
	}
	else
	{
		if(formal_pin == private_led_pin_04)
		{
			digitalWrite(private_led_pin_03, LOW);
			digitalWrite(private_led_pin_04, HIGH);
			digitalWrite(private_led_pin_05, LOW);
		}
		else
		{
			if(formal_pin == private_led_pin_05)
			{
				digitalWrite(private_led_pin_03, LOW);
				digitalWrite(private_led_pin_04, LOW);
				digitalWrite(private_led_pin_05, HIGH);
			}
		}
	}
}


void Lights::call_into_lights(void * p)
{
	((Lights *)p)->burn();
}


void Lights::call_into_flash(void * p)
{
	((Lights *)p)->flash();
}


void Lights::call_into_traffic(void * p)
{
	((Lights *)p)->traffic();
}



