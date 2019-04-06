#include <Arduino.h>

// connect motor controller pins to Arduino digital pins
// motor one
int enA = 11;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 7;
int in3 = 6;
int in4 = 5;

int SIGNAL_PIN = LED_BUILTIN;
int SIGNAL_DELAY = 300; // Delay in m

void demoOne();
void demoTwo();

void setup()
{
  pinMode(SIGNAL_PIN, OUTPUT);
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}


void blink_three()
{
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(SIGNAL_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(SIGNAL_DELAY);                       // wait for a second
    digitalWrite(SIGNAL_PIN, LOW);    // turn the LED off by making the voltage LOW
    delay(SIGNAL_DELAY);  
  } 
}

void demoZero()
{
  blink_three();

  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed, possible range 0~255
  analogWrite(enA, 255);

  delay(2000);

  // turn on motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  analogWrite(enA, 0);
}

void demoOne()
{
  blink_three();
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
  delay(2000);
  // now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  delay(2000);
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


void demoTwo()
{
  blink_three();
  // this function will run the motors across the range of possible speeds
  // note that maximum speed is determined by the motor itself and the operating voltage
  // the PWM values sent by analogWrite() are fractions of the maximum speed possible 
  // by your hardware
  // turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  // accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  } 
  // decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  } 
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  
}
void loop()
{
  demoZero();
  delay(1000);

  demoOne();
  delay(1000);
  demoTwo();
  delay(1000);
}