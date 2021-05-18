//Author Jonathan Rubin
//rgbled driver code, contains definitions for functions and defines values for timer
	#include <MKL25Z4.h>
	#include <stdint.h>
	#define RED_LED_LOCATION 18
	#define GREEN_LED_LOCATION 19
	#define BLUE_LED_LOCATION 1
	#ifndef TOP
	#define TOP 256
	#endif
	#ifndef PRESCALE_VALUE
	#define PRESCALE_VALUE 7
	#endif

	void configure_rgbled()
	{
	//RED LED
		SIM -> SCGC5 |= SIM_SCGC5_PORTB_MASK;
		PORTB -> PCR[RED_LED_LOCATION] = (PORTB->PCR[RED_LED_LOCATION] & ~(PORT_PCR_MUX_MASK | 	PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(3) | PORT_PCR_IRQC(0);
		PTB -> PDDR |= (1<<RED_LED_LOCATION);

	//GREEN LED
		PORTB -> PCR[GREEN_LED_LOCATION] = (PORTB->PCR[GREEN_LED_LOCATION] & ~(PORT_PCR_MUX_MASK | PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(3) | PORT_PCR_IRQC(0);
		PTB -> PDDR |= (1<<GREEN_LED_LOCATION);


	//BLUE LED
		SIM ->SCGC5 |= SIM_SCGC5_PORTD_MASK;
		PORTD ->PCR[BLUE_LED_LOCATION] = (PORTD->PCR[BLUE_LED_LOCATION] & ~(PORT_PCR_MUX_MASK | PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(4) | PORT_PCR_IRQC(0);
		PTD ->PDDR |= (1<<BLUE_LED_LOCATION);

		//setup Timer 0
		SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
		TPM0->SC = TPM_SC_CPWMS(0) | TPM_SC_PS(PRESCALE_VALUE);
		TPM0->MOD=TOP-1;
		//Setup TPM0 Ch1
		TPM0->CONTROLS[1].CnSC = TPM_CnSC_ELSA(1) | TPM_CnSC_ELSB(1)
					| TPM_CnSC_MSA(0) | TPM_CnSC_MSB(1);

		SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
		TPM2->SC = TPM_SC_CPWMS(0) | TPM_SC_PS(PRESCALE_VALUE);
		TPM2->MOD=TOP-1;

		TPM2->CONTROLS[0].CnSC = TPM_CnSC_ELSA(1) | TPM_CnSC_ELSB(1)
					| TPM_CnSC_MSA(0) | TPM_CnSC_MSB(1);

		TPM2->CONTROLS[1].CnSC = TPM_CnSC_ELSA(1) | TPM_CnSC_ELSB(1)
					| TPM_CnSC_MSA(0) | TPM_CnSC_MSB(1);

		//Start timer
		TPM0->SC |= TPM_SC_CMOD(01);
		TPM2->SC |= TPM_SC_CMOD(01);
	}

	void set_red_level(uint8_t level)
	{
		TPM2->CONTROLS[0].CnV = level;
	}
	void turn_on_red()
	{
		PTB ->PCOR |= (1<<RED_LED_LOCATION);
	}
	void turn_off_red()
	{
		PTB ->PSOR |= (1<<RED_LED_LOCATION);
	}
	void toggle_red()
	{
		PTB ->PTOR |= (1<<RED_LED_LOCATION);
	}


	void set_green_level(uint8_t level)
	{
		TPM2->CONTROLS[1].CnV = level;
	}
	void turn_on_green()
	{
		PTB ->PCOR |= (1<<GREEN_LED_LOCATION);
	}
	void turn_off_green()
	{
		PTB ->PSOR |= (1<<GREEN_LED_LOCATION);
	}
	void toggle_green()
	{
		PTB ->PTOR |= (1<<GREEN_LED_LOCATION);
	}


	void set_blue_level(uint8_t level)
	{
		TPM0->CONTROLS[1].CnV = level;
	}
	void turn_on_blue()
	{
		PTD ->PCOR |= (1<<BLUE_LED_LOCATION);
	}
	void turn_off_blue()
	{
		PTD ->PSOR |= (1<<BLUE_LED_LOCATION);
	}
	void toggle_blue()
	{
		PTD ->PTOR |= (1<<BLUE_LED_LOCATION);
	}

	void set_rgbled_color_to(uint8_t red, uint8_t green, uint8_t blue)
	{
		set_red_level(red);
		set_green_level(green);
		set_blue_level(blue);
	}

	void turn_off_rgbled()
	{
		set_rgbled_color_to(0x00,0x00,0x00);
	}



