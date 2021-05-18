//Author: Jonathan Rubin
//SysTick Timer driver, contains functions for handling systick interrupts on periodic timings

#include <stdint.h>
#include <MKL25Z4.h>
#include <stdbool.h>

#ifndef SYSTICK_PERIOD
#define SYSTICK_PERIOD 1000 // in us
#endif

#define SYSTICK_TOP_VAL (SYS_CLOCK / SYSTICK_PERIOD)

#if SYSTICK_TOP_VAL > (1<<24 -1)
#error SYSTICK_PERIOD is too large
#endif

static volatile  _Bool systick_irq;

void configure_systick()
{
	//configure CTRL
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
			SysTick_CTRL_ENABLE_Msk |
			SysTick_CTRL_TICKINT_Msk;

	//Set Period in LOAD
	SysTick->LOAD = SYSTICK_TOP_VAL;
}

_Bool SysTick_has_fired()
{
	if(systick_irq)
	{
		systick_irq=0;
		return 1;
	}
	else	return false;
}

void SysTick_Handler()
{
	systick_irq=1;
}
