// I2C testing 
// Recieve any characters, write them to 2 pins
// Use for blinking both the internal LED, and an external LED
// adapted M. Jones 2019
//
// Modified from: Wire Slave Receiver by Nicholas Zambetti <http://www.zambetti.com>

#include <Wire.h>
#include <Arduino.h>

const int kLedBuiltin = LED_BUILTIN; // onboard LED
const int kLedPin = 12; // onboard LED
const int k_I2C_Address = 0x9; // Specify the I2C address here
void receiveEvent(int howMany);

void setup() {
  Wire.begin(k_I2C_Address); // join i2c 
  Wire.onReceive(receiveEvent); // register event
  pinMode(kLedPin, OUTPUT);
  pinMode(kLedBuiltin, OUTPUT);
  digitalWrite(kLedPin, LOW); // turn it off
  digitalWrite(kLedBuiltin, LOW); // turn it off
}

void loop() {
  delay(100);
}
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    digitalWrite(kLedPin, c);
    digitalWrite(kLedBuiltin, c);
  }
}

