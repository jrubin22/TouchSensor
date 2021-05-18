//Jonathan Rubin
//Grad Project 2021
//Touch Sensor Header File, contains defines for electrodes, thresholds, declares and initializes variables, prototypes functions

#ifndef TOUCHSENSOR_H
#define TOUCHSENSOR_H
#include <stdint.h>

#define NO_TOUCH			0
#define SLIDER_LENGTH		40
#define TOTAL_ELECTRODE		2

//define which channels match up to which electrode
#define ELECTRODE0   9
#define ELECTRODE1   10
#define ELECTRODE2   0
#define ELECTRODE3   1
#define ELECTRODE4   2
#define ELECTRODE5   3
#define ELECTRODE6   4
#define ELECTRODE7   5
#define ELECTRODE8   6
#define ELECTRODE9   7
#define ELECTRODE10  8
#define ELECTRODE11  11
#define ELECTRODE12  12
#define ELECTRODE13  13
#define ELECTRODE14  14
#define ELECTRODE15  15

//can define individual threshold values for each electrode
#define THRESHOLD0   100
#define THRESHOLD1   100
#define THRESHOLD2   100
#define THRESHOLD3   100
#define THRESHOLD4   100
#define THRESHOLD5   100
#define THRESHOLD6   100
#define THRESHOLD7   100
#define THRESHOLD8   100
#define THRESHOLD9   100
#define THRESHOLD10   100
#define THRESHOLD11   100
#define THRESHOLD12   100
#define THRESHOLD13   100
#define THRESHOLD14   100
#define THRESHOLD15   100


//variables
 

static uint16_t base[16] = {NO_TOUCH,NO_TOUCH,NO_TOUCH,NO_TOUCH,
									NO_TOUCH,NO_TOUCH,NO_TOUCH,NO_TOUCH,
									NO_TOUCH,NO_TOUCH,NO_TOUCH,NO_TOUCH,
									NO_TOUCH,NO_TOUCH,NO_TOUCH,NO_TOUCH};

 static uint16_t Change[16];
 static uint8_t SliderPercent[16] = {NO_TOUCH,NO_TOUCH,NO_TOUCH,NO_TOUCH,
									NO_TOUCH,NO_TOUCH,NO_TOUCH,NO_TOUCH,
									NO_TOUCH,NO_TOUCH,NO_TOUCH,NO_TOUCH,
									NO_TOUCH,NO_TOUCH,NO_TOUCH,NO_TOUCH};
 static uint8_t SliderDistance[16] = {NO_TOUCH,NO_TOUCH,NO_TOUCH,NO_TOUCH,
									NO_TOUCH,NO_TOUCH,NO_TOUCH,NO_TOUCH,
									NO_TOUCH,NO_TOUCH,NO_TOUCH,NO_TOUCH,
									NO_TOUCH,NO_TOUCH,NO_TOUCH,NO_TOUCH};
									


 static uint8_t end_flag = 1;

 static uint8_t total_electrode = TOTAL_ELECTRODE;

 static uint8_t electrode_arrays[16]={ELECTRODE0,ELECTRODE1,ELECTRODE2,ELECTRODE3,ELECTRODE4,ELECTRODE5,
									 ELECTRODE6,ELECTRODE7,ELECTRODE8,ELECTRODE9,ELECTRODE10,ELECTRODE11,
									 ELECTRODE12,ELECTRODE13,ELECTRODE14,ELECTRODE15};
									 
									 


 static uint8_t last_percent = 0;
 static uint8_t current_percent = 0;
 
 static uint8_t ongoing_elec=0;
 static uint8_t count = 0;

 static uint32_t AbsolutePercent = NO_TOUCH;
 static uint32_t AbsoluteDistance = NO_TOUCH;




//functions

void configure_touchSensor();
void calibrate_touch();
void read_baseline_values();
void start_software_scan();
uint16_t read_data();


void ElectrodeRead();
void slider_read();

_Bool is_Touched();


uint8_t read_percent();
uint8_t read_distance();

uint8_t slide_level(uint8_t red_level);
_Bool touch_above(uint8_t percentMin);
uint8_t partitions3(uint8_t percent1, uint8_t percent2);
uint8_t partitions4(uint8_t percent1, uint8_t percent2, uint8_t percent3);



#endif