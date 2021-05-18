//Jonathan Rubin
//Grad Project 2021
//Touch Sensor File, defines functions for touch sensor

#include <TouchSensor.h>

#include <MKL25Z4.h>
#include <stdbool.h>
#include <stdint.h>



 static volatile _Bool tsi_irq=0; 

 




void configure_touchSensor()
{
	tsi_irq=0;
	
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK;
		
	TSI0->GENCS |= (TSI_GENCS_ESOR_MASK		
                | TSI_GENCS_MODE(0)			//Set TSI to non-noise detecting mode
                | TSI_GENCS_REFCHRG(4)		//set reference oscillator charge/dischare I to 8uA
                | TSI_GENCS_DVOLT(0)		//Oscillator voltage rails to preset 00
                | TSI_GENCS_EXTCHRG(7)		//set electrode oscillator charge/discharge I to 64uA
                | TSI_GENCS_PS(4)			//set oscillator frequency to be divided by 4 prescaler
                | TSI_GENCS_NSCN(11)		//Scan 10 times per electrode
                | TSI_GENCS_TSIIEN_MASK		//Touch sensing input Interrupt enable
                | TSI_GENCS_STPE_MASK 		//works in low power mode
				
                );
    TSI0->GENCS &= ~TSI_GENCS_STM_MASK;		//Set trigger to software trigger
	
	TSI0->GENCS |= TSI_GENCS_TSIEN_MASK; //enable tsi module
	  
	NVIC_EnableIRQ(TSI0_IRQn);
	
	calibrate_touch();
		
}


void calibrate_touch()
{
	_Bool tsi_trigger_mode = 1;
	
	
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK;
	TSI0->GENCS &= ~TSI_GENCS_TSIEN_MASK;
	
	if(TSI0->GENCS & TSI_GENCS_STM_MASK)
	{
		tsi_trigger_mode = true;
	}
	else tsi_trigger_mode = false;

	
	read_baseline_values();

	TSI0->GENCS |= TSI_GENCS_TSIIEN_MASK; //Enable TSI interrupt
	
	if(tsi_trigger_mode) //restore mode to what it was before calibration
	{
		TSI0->GENCS |= TSI_GENCS_STM_MASK;
	}
	else
		TSI0->GENCS &= ~TSI_GENCS_STM_MASK;
	
	TSI0->GENCS &= ~TSI_GENCS_STM_MASK;

	TSI0->GENCS |= TSI_GENCS_TSIEN_MASK; //turn touch module back on	

}

void read_baseline_values()
{
	TSI0->GENCS &= ~TSI_GENCS_STM_MASK;      
    TSI0->GENCS &= ~TSI_GENCS_TSIIEN_MASK;
	
	TSI0->GENCS |= TSI_GENCS_TSIEN_MASK;

	
	
	for(count = 0; count < total_electrode; count++)
	{
		TSI0->DATA = ((electrode_arrays[count] << TSI_DATA_TSICH_SHIFT));
		start_software_scan();
		
		base[count] = (read_data());
	}
	
	TSI0->GENCS &= ~TSI_GENCS_TSIEN_MASK; //Disable TSI Module	
	
}

void start_software_scan()
{
	TSI0->GENCS |= TSI_GENCS_TSIEN_MASK; //turn touch module on
	TSI0->DATA |= TSI_DATA_SWTS_MASK;
	while(!(TSI0->GENCS & TSI_GENCS_EOSF_MASK));//wait for end of scan
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK;//clear end of scan mask by writing to reg
	end_flag = 1;
	

}

uint16_t read_data()
{
	return (TSI0->DATA & TSI_DATA_TSICNT_MASK);
}


 void ElectrodeRead()
{
	static uint16_t touchCount[16];

	uint16_t temp_change;
	
	touchCount[ongoing_elec] = (TSI0->DATA & TSI_DATA_TSICNT_MASK); //Store scan counter value
	temp_change = touchCount[ongoing_elec] - base[ongoing_elec];    //gets delta value counter - calibrated value that will later be compared to threshold
	if(temp_change < 0)
	{
		Change[ongoing_elec] = 0;
	}
	else Change[ongoing_elec] = temp_change;

	if(total_electrode > 1)
	{
		if((total_electrode-1)> ongoing_elec)
			ongoing_elec++;
		else
			ongoing_elec = 0;
		
		TSI0->DATA = ((electrode_arrays[ongoing_elec] << TSI_DATA_TSICH_SHIFT));
		TSI0->DATA |= TSI_DATA_SWTS_MASK;
	}


	
	}


void slider_read()
{
	uint16_t threshold = 300; //can use this if all thresholds are the same
	
	//use below if you want different thresholds for each electrode
	/*uint16_t thresholds[16] = {THRESHOLD0,THRESHOLD1,THRESHOLD2,THRESHOLD3,THRESHOLD4,THRESHOLD5,
							THRESHOLD6,THRESHOLD7,THRESHOLD8,THRESHOLD9,THRESHOLD10,THRESHOLD11,
                            THRESHOLD12,THRESHOLD13,THRESHOLD14,THRESHOLD15};
	*/
	

	if(end_flag)
	{
		end_flag=0;
		if((Change[0]>threshold || Change[1]>threshold ))
		{
			SliderPercent[0] = (Change[0]*100)/(Change[0]+Change[1]);
			SliderPercent[1] = (Change[1]*100)/(Change[0]+Change[1]);
			SliderDistance[0] = ((SliderPercent[0] * SLIDER_LENGTH)/100);
			SliderDistance[1] = ((SliderPercent[1] * SLIDER_LENGTH)/100);
			AbsoluteDistance = (((SLIDER_LENGTH - SliderDistance[0]) + SliderDistance[1]) >> 1);
			AbsolutePercent = (((100 - SliderPercent[0]) + SliderPercent[1]) >> 1);
			
		}
		else
		{
			SliderPercent[0] = NO_TOUCH;
			SliderPercent[1] = NO_TOUCH;
			SliderDistance[0] = NO_TOUCH;
			SliderDistance[1] = NO_TOUCH;
			AbsoluteDistance = NO_TOUCH;
			AbsolutePercent = NO_TOUCH;
		}

	}

}


_Bool is_Touched()
{
	if(tsi_irq)
	{
		tsi_irq=0;
		return true;
	}
	else return false;
	
}



uint8_t read_percent()
{
	slider_read();
	return AbsolutePercent;
}

uint8_t read_distance()
{
	slider_read();
	return AbsoluteDistance;
}




uint8_t slide_level(uint8_t red_level)
{
	last_percent = current_percent;
	current_percent = read_percent();
		if(current_percent > last_percent)
		{
			if (red_level <0xFF)
			{
				return ++red_level;
			}
			return 0xFF;
		}
		if(current_percent < last_percent)
		{
			if(red_level > 0x00)
			{
				return --red_level;
			}
			return 0;
		}
		else return red_level;
}

_Bool touch_above(uint8_t percentMin)
{
	if(read_percent() >= percentMin)
	{
		return true;
	}
	else return false;
	
	
}

uint8_t partitions4(uint8_t percent1, uint8_t percent2, uint8_t percent3)
{
	uint8_t region = 0;
	if(touch_above(percent3))
	{
		region |= 1<<3;
	}
	else if(touch_above(percent2))
	{
		region |= 1<<2;
	}
	else if(touch_above(percent1))
	{
		region |= 1<<1;
	}
	else if(touch_above(1))
	{
		region |= 1<<0;
	}
	return region;
	
}

uint8_t partitions3(uint8_t percent1, uint8_t percent2)
{
	uint8_t region = 0;
	if(touch_above(percent2))
	{
		region |= 1<<2;
	}
	else if(touch_above(percent1))
	{
		region |= 1<<1;
	}
	else if(touch_above(1))
	{
		region |= 1<<0;
	}
	return region;
	
}
	


void TSI0_IRQHandler()
{
	tsi_irq = 1;
	end_flag = 1;
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK;
	ElectrodeRead();
}