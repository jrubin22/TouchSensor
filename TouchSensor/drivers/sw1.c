//Jonathan Rubin & Garrett Robinson
//Switch1 driver file.  contains functions for pressing button, and configuring

	#define SW1_LOCATION 20
	#include <MKL25Z4.h>
	#include <stdint.h>
	#include <stdbool.h>
	enum switch_state {WAIT_PRESS, WAIT_RELEASE};
	static enum switch_state state = WAIT_PRESS;

	void configure_sw1()
	{
		SIM ->SCGC5 |= SIM_SCGC5_PORTA_MASK;
		PORTA ->PCR[SW1_LOCATION] = (PORTA->PCR[SW1_LOCATION] &~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) |PORT_PCR_MUX(1) | PORT_PCR_IRQC(0);
		PTA->PDDR &= ~(1<<SW1_LOCATION);
	}

	void delay( uint32_t time_del)
	{
		volatile uint32_t counter;
		while (time_del--)
		{
			counter = 1500;
			while(counter--);
		}
	}

	_Bool sw1_is_not_pressed()
	{
		return (PTA->PDIR & (1<<SW1_LOCATION));
	}

	_Bool sw1_is_pressed()
	{
		return (!sw1_is_not_pressed());
	}

	_Bool press_and_release()
	{
		switch(state)
		{
			default:
			case WAIT_PRESS:
				if(sw1_is_pressed())
				{
					state = WAIT_RELEASE;
					delay(100);
					return 0;
				}
				else
				{
					state = WAIT_PRESS;
					delay(100);
					return 0;
				}
				break;
			case WAIT_RELEASE:
				if(sw1_is_not_pressed())
				{
					state = WAIT_PRESS;
					//delay(000);
					return 1;

				}
				else
				{
					state = WAIT_RELEASE;
					delay(100);
					return 0;
				}
				break;


		}

	}
