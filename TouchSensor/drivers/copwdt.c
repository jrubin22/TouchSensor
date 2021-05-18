//Author Jonathan Rubin
//Driver file for copwdt, configures copwdt timer, and has function to feed watchdog

#include <MKL25Z4.h>

#ifndef COP_TIMEOUT_SELECT
#define COP_TIMEOUT_SELECT 3
#endif

void configure_copwdt()
{
	SIM->COPC = SIM_COPC_COPT(COP_TIMEOUT_SELECT) |
#ifdef COPWDT_WINDOWED_MODE
		    SIM_COPC_COPW(1) |
#endif
#ifdef COPWDT_CLOCK_BUSCLK
		    SIM_COPC_COPCLKS(1) |
#endif
		0;
}
void feed_the_watchdog()
{
	SIM->SRVCOP = 0x55;
	SIM->SRVCOP = 0xAA;
}
