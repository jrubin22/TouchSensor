//Author: Jonathan Rubin
//Header for SysTick Timer driver

#ifndef SYSTICKTIMER_H
#define SYSTICKTIMER_H
#include <stdbool.h>
void configure_systick();
_Bool SysTick_has_fired();
#endif
