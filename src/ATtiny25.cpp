#include "ATtiny25.h"
#include "Arduino.h"
#include <inttypes.h>
#include <Wire.h>

ATtiny25::ATtiny25()
{
}

// returns the moisture percentage from 0 to 100
int ATtiny25::readMoisture(){
  Wire.beginTransmission(ATTINY25_I2CADDR);
  Wire.write(1);
  Wire.endTransmission();
  delay(5);
  int c=0;
  Wire.requestFrom(ATTINY25_I2CADDR, 2);
  if(Wire.available()==2)
  { 
    c = Wire.read();
    c <<= 8;
    c |= Wire.read();
    c = constrain(c, MIN_CAP_READ, MAX_CAP_READ);
    c = map(c, MIN_CAP_READ, MAX_CAP_READ, 0, 100);
  }
  return c;
}

// returns the temperature reading from the sensor in degrees Celsius
float ATtiny25::readTemp() {
  Wire.beginTransmission(ATTINY25_I2CADDR);
  Wire.write(2);
  Wire.endTransmission();
  delay(5);
  int c = 0;
  Wire.requestFrom(ATTINY25_I2CADDR, 2);
  if (Wire.available() == 2)
  {
    c = Wire.read();
    c <<= 8;
    c |= Wire.read();
    //https://learn.adafruit.com/thermistor/using-a-thermistor thanks!
    uint32_t adcVal = ANALOG_READ_MAX - c;
    uint32_t resistance = (SERIES_RESISTOR * ANALOG_READ_MAX) / adcVal - SERIES_RESISTOR;
    float steinhart = (float)resistance / THERMISTOR_NOMINAL;     // (R/Ro)
    steinhart = log(steinhart);                  // ln(R/Ro)
    steinhart /= B_COEFFICIENT;                   // 1/B * ln(R/Ro)
    steinhart += 1.0 / (TEMPERATURE_NOMINAL + 273.15); // + (1/To)
    steinhart = 1.0 / steinhart;                 // Invert
    steinhart -= 273.15;                         // convert to C
    return steinhart;
  }
  return c;
}