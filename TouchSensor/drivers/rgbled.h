//Author: Jonathan Rubin
//RGBLED Driver header, contains enums, defines and function prototypes

#ifndef RGBLED_H
#define RGBLED_H
#ifndef TOP
#define TOP 256
#endif
#include <stdint.h>
	void configure_rgbled();
	void set_red_level(uint8_t level);
	void turn_on_red();
	void turn_off_red();
	void toggle_red();
	void set_green_level(uint8_t level);
	void turn_on_green();
	void turn_off_green();
	void toggle_green();
	void set_blue_level(uint8_t level);
	void turn_on_blue();
	void turn_off_blue();
	void toggle_blue();
	void set_rgbled_color_to(uint8_t red, uint8_t green, uint8_t blue);
	void turn_off_rgbled();
#endif
