#include <Arduino.h>
/*
Spin up and down slow, 
Control left and right, alternate 
*/

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

int TRK_START_PWM = 100;
int TRK_STOP_PWM = 256;
int TRK_STEP_PWM = 5;

char str[50];

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

void left_forward()
{
  // turn on motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // accelerate
  for (int i = TRK_START_PWM; i < TRK_STOP_PWM; i = i + TRK_STEP_PWM)
  {
    sprintf(str, "%d\n", i);
    Serial.print(str);
    analogWrite(enA, i);
    delay(20);
  }

  // decelerate
  for (int i = TRK_STOP_PWM; i >= TRK_START_PWM; i = i - TRK_STEP_PWM)
  {
    sprintf(str, "%d\n", i);
    Serial.print(str);
    analogWrite(enA, i);
    delay(20);
  }

  // Turn off
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  sprintf(str, "Finished LEFT\n");
  Serial.print(str);
}

void right_forward()
{
  // turn on motor
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  // accelerate
  for (int i = TRK_START_PWM; i < TRK_STOP_PWM; i = i + TRK_STEP_PWM)
  {
    sprintf(str, "%d\n", i);
    Serial.print(str);
    analogWrite(enB, i);
    delay(20);
  }

  // decelerate
  for (int i = TRK_STOP_PWM; i >= TRK_START_PWM; i = i - TRK_STEP_PWM)
  {
    sprintf(str, "%d\n", i);
    Serial.print(str);
    analogWrite(enB, i);
    delay(20);
  }
  // Turn off
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  sprintf(str, "Finished RIGHT\n");
  Serial.print(str);
}

void loop()
{
  left_forward();
  delay(1000);
  right_forward();
  delay(1000);
}