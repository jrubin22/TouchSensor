//Author: Jonathan Rubin
//Switch 1 driver, contains functions to initialize switch, and to see if pressed or not pressed

#ifndef SW1_H
#define SW1_H
	#include <stdbool.h>
	void configure_sw1();
	_Bool sw1_is_not_pressed();
	_Bool sw1_is_pressed();
	_Bool press_and_release();
#endif

