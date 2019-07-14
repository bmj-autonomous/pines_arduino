// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

// 04-Feb-2018 mcarter adapted
#include <Wire.h>
#include <Arduino.h>

const int kLedPin = 12; // onboard LED
const int k_I2C_Address = 0x8 // Specify the I2C address here
const h
// static_assert(LOW == 0, "Expecting LOW to be 0");
void receiveEvent(int howMany);


void setup() {
  static_assert(LOW == 0, "Expecting LOW to be 0");
  Wire.begin(k_I2C_Address); // join i2c 
  Wire.onReceive(receiveEvent); // register event
  pinMode(kLedPin, OUTPUT);
  digitalWrite(kLedPin, LOW); // turn it off
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
  }
}

