# TouchSensor

# Touch Sensor.c

first run configure_touchSensor(); which will turn on the TSI module, as well as configure the TSI0 GENCS register to baseline values for use mode and turn on the interrupt enables.
This will also call calibrate_touch(); which will initialize the sensor and zero it by calling read_baseline_values();
read_baseline_values(); scans all active electrodes (denoted by the total_electrodes define statement in TouchSensor.h) with the start_software_scan(); function.
start_software_scan(); turns on the module, sets the SWTS flag high to start a software scan, then waits for the scan to end.  After this, the value is read by read_data(); function, which returns the tsi count from the TSI_DATA register.
The IRQ handler will then call the ElectrodeRead() function.  This will compare the current electrode values to the baseline zeroed values. Then the value is stored in an array Change with the index being the electrode that is being scanned.
The slider_read(); function compares the Change of electrodes to a defined threshold (either general threshold or a threshold defined for each electrode).  If the change is greater then the threshold then that means the slider is being touched.

Implemented the algorithm as defined by the MBED library for the TSI sensor, where the percent touched on the slider for  is defined as the current electrodes change * 100 divided by both electrode's change added together.  The distance is then defined as the percent times the length in mm divided by 100.

The functions implemented in the test file are slide_level(led_level); touch_above(uint8_t percentMin); partitions3(uint8_t percent1, uint8_t percent2); and partitions4(uint8_t percent1, uint8_t percent2, uint8_t percent3);

slide_level compares the current percentage to the percentage at the last call of the function slide_level, and will either return an incremented value or a decremented value of the parameter the function takes in.

touch_above takes a percentage level as the argument, and compares the current touched location on the board to the argument.  If the sensor is touched above the minimum, then it returns true, otherwise returns false.

partitions3 and partitions4, use the touch_above function to seperate the sensor into either 3 or 4 segments respectively, and return a uint8_t that will return either 0x08, 0x04, 0x02, 0x01, or 0x00 with the high bit being the region that is being touched.


# TestTouchSensor.c

TestTouchSensor first configures all peripherals, then enables irq.
in the main function loop the code will wait for systick before looping.  Will check is_start, which is initialized to 0, start the software scan once, then set is_start high.

the first commented block will test slide_level function
the second commented block wil test the touch_above function
the third commented block will test the partitions4 function
the fourth block of code, not commented out will test partitions3 function.
after these block of function implementations, the code will set the rgbled to a color defined by the above functions, then feed the watchdog and loop.
