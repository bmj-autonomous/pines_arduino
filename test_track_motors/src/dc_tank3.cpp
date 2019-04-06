#include <Arduino.h>
/*
Spin up and down slow, 
Control forward, backward
*/

// connect motor controller pins to Arduino digital pins
// motor one
int enA_right = 11;
int in1_right = 9;
int in2_right = 8;
// motor two
int enB_left = 7;
int in3_left = 6;
int in4_left = 5;

int SIGNAL_PIN = LED_BUILTIN;
int SIGNAL_DELAY = 300; // Delay in m

int TRK_START_PWM = 100;
int TRK_STOP_PWM = 256;
int TRK_STEP_PWM = 1;

char str[50];

void setup()
{
  pinMode(SIGNAL_PIN, OUTPUT);
  // set all the motor control pins to outputs
  pinMode(enA_right, OUTPUT);
  pinMode(enB_left, OUTPUT);
  pinMode(in1_right, OUTPUT);
  pinMode(in2_right, OUTPUT);
  pinMode(in3_left, OUTPUT);
  pinMode(in4_left, OUTPUT);
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

void backward()
{
  // turn on motors
  digitalWrite(in1_right, LOW);
  digitalWrite(in2_right, HIGH);
  digitalWrite(in3_left, HIGH);
  digitalWrite(in4_left, LOW);

  // accelerate
  for (int i = TRK_START_PWM; i < TRK_STOP_PWM; i = i + TRK_STEP_PWM)
  {
    sprintf(str, "%d\n", i);
    Serial.print(str);
    analogWrite(enA_right, i);
    analogWrite(enB_left, i);
    // analogWrite(enb, i);
    delay(20);
  }

  // decelerate
  for (int i = TRK_STOP_PWM; i >= TRK_START_PWM; i = i - TRK_STEP_PWM)
  {
    // sprintf(str, "%d\n", i);
    // Serial.print(str);
    analogWrite(enA_right, i);
    analogWrite(enB_left, i);
    delay(20);
  }

  // Turn off
  digitalWrite(in1_right, LOW);
  digitalWrite(in2_right, LOW);
  analogWrite(enA_right, 0);

  digitalWrite(in3_left, LOW);
  digitalWrite(in4_left, LOW);
  analogWrite(enB_left, 0);

  sprintf(str, "Finished LEFT\n");
  Serial.print(str);
}


void forward()
{
  // turn on motors
  digitalWrite(in1_right, HIGH);
  digitalWrite(in2_right, LOW);
  digitalWrite(in3_left, LOW);
  digitalWrite(in4_left, HIGH);

  // accelerate
  for (int i = TRK_START_PWM; i < TRK_STOP_PWM; i = i + TRK_STEP_PWM)
  {
    sprintf(str, "%d\n", i);
    Serial.print(str);
    analogWrite(enA_right, i);
    analogWrite(enB_left, i);
    // analogWrite(enb, i);
    delay(20);
  }

  // decelerate
  for (int i = TRK_STOP_PWM; i >= TRK_START_PWM; i = i - TRK_STEP_PWM)
  {
    // sprintf(str, "%d\n", i);
    // Serial.print(str);
    analogWrite(enA_right, i);
    analogWrite(enB_left, i);
    delay(20);
  }

  // Turn off
  digitalWrite(in1_right, LOW);
  digitalWrite(in2_right, LOW);
  analogWrite(enA_right, 0);

  digitalWrite(in3_left, LOW);
  digitalWrite(in4_left, LOW);
  analogWrite(enB_left, 0);

  sprintf(str, "Finished LEFT\n");
  Serial.print(str);
}


void loop()
{
  forward();
  delay(1000);
  backward();
  delay(1000);
}