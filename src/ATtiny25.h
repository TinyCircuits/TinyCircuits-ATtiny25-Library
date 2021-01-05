#ifndef ATTINY25_h
#define ATTINY25_h

// Communication address with the sensor
#define ATTINY25_I2CADDR     0x30

#define MIN_CAP_READ 710 /* Toggle this to raw minimum value */
#define MAX_CAP_READ 975 /* Toggle this to raw maximum value */

#define ANALOG_READ_MAX 1023
#define THERMISTOR_NOMINAL 10000
#define TEMPERATURE_NOMINAL 25
#define B_COEFFICIENT 3380
#define SERIES_RESISTOR 35000

#include <inttypes.h>

class ATtiny25 {
public:
	ATtiny25();
	int readMoisture();
	float readTemp();
};

#endif