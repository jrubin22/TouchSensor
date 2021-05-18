//Jonathan Rubin
//Grad Project 2021
//Touch Sensor Test File


#include <rgbled.h>
#include <sw1.h>
#include <TouchSensor.h>
#include <MKL25Z4.h>
#include <stdbool.h>
#include <copwdt.h>
#include <systicktimer.h>
#include <stdint.h>


void main()
{
	__disable_irq();
	configure_sw1();
	configure_rgbled();
	configure_systick();
	configure_copwdt();
	configure_touchSensor();
	__enable_irq();

	_Bool is_start = 0;
	uint8_t red_level = 0x0F;
	uint8_t green_level = 0x0F;
	uint8_t blue_level = 0x0F;
	
	
	uint8_t parts = 0x00;
	//uint8_t distances[2] = {0,0}
	
	set_rgbled_color_to(0x0F,0x00,0x00);
	
	while(1)
	{
		asm("wfi");
		if(!SysTick_has_fired())
			continue;
		if(!is_start)
		{
			start_software_scan();
			is_start=1;
		}
		
		//red_level = slide_level(red_level);
		
		
		/*
		
		if(touch_above(50))
		{
			red_level=0x0F;
		}
		else red_level=0x00;
		
		*/
		
		/*
		
		parts=partitions4(25,50,75);
		if(parts & 0x04)
		{
			red_level = 0x0F;
			green_level=0x00;
			blue_level=0x00;
		}
		else if(parts & 0x02)
		{
			red_level=0x00;
			green_level=0x0F;
			blue_level=0x00;
		}
		else if(parts & 0x01)
		{
			red_level=0x00;
			green_level=0x00;
			blue_level=0x0F;		
		}
		else if (parts &0x08)
		{
			red_level=0x0F;
			green_level=0x0F;
			blue_level=0x0F;
		}
		else if (!parts)
		{
			red_level=0x00;
			green_level=0x00;
			blue_level=0x00;
		}
		
		*/
		
		
		parts = partitions3(33,66);
		if(parts & 0x02)
		{
			red_level=0x00;
			green_level=0x0F;
			blue_level=0x00;
		}
		else if(parts & 0x01)
		{
			red_level=0x00;
			green_level=0x00;
			blue_level=0x0F;		
		}
		else if (parts &0x04)
		{
			red_level=0x0F;
			green_level=0x00;
			blue_level=0x00;
		}
		else if (!parts)
		{
			red_level=0x00;
			green_level=0x00;
			blue_level=0x00;
		}
		set_rgbled_color_to(red_level,green_level,blue_level);
		
		
		feed_the_watchdog();
		
	}
}