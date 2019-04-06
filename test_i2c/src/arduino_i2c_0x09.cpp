/* Minimum example for i2c bus
Change the address number and upload for i2c testing
*/
#include <Arduino.h>
#include <Wire.h>

// I2C settings
int i2c_address = 0x09;

void setup() {
  // I2C setup
  Wire.begin(i2c_address);      // join i2c bus with address #8
}

void loop()
{
}