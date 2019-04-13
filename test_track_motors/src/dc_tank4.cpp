#include <Wire.h>
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
int TRK_STOP_PWM = 255;
int TRK_STEP_PWM = 1;

char str[50];

const int ledPin = 12; // onboard LED

void receiveEvent(int howMany);
void move_square();

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

  static_assert(LOW == 0, "Expecting LOW to be 0");
  Wire.begin(0x8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // turn it off
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

void forward_constant(int speed, int time_milli)
{
  // turn on motors
  digitalWrite(in1_right, LOW);
  digitalWrite(in2_right, HIGH);
  digitalWrite(in3_left, HIGH);
  digitalWrite(in4_left, LOW);

  // move
  sprintf(str, "%d\n", speed);
  Serial.print(str);
  analogWrite(enA_right, speed);
  analogWrite(enB_left, speed);

  //wait
  delay(time_milli);

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

// direction = 1 => right
// direction = 0 => left
void turn_constant(int speed, int turn_delay, int direction)
{
  // turn on motors
  if(direction)
  {
    //left
    digitalWrite(in1_right, LOW);
    digitalWrite(in2_right, HIGH);
    
    digitalWrite(in3_left, LOW);
    digitalWrite(in4_left, HIGH);
  } else {
    //right
    digitalWrite(in1_right, HIGH);
    digitalWrite(in2_right, LOW);
    
    digitalWrite(in3_left, HIGH);
    digitalWrite(in4_left, LOW);
  }

  // move
  sprintf(str, "%d\n", speed);
  Serial.print(str);
  analogWrite(enA_right, speed);
  analogWrite(enB_left, speed);

  //wait
  delay(turn_delay);

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
  delay(6000);
  /*
  forward();
  delay(1000);
  backward();
  delay(1000);
  // */

  /*
  digitalWrite(in1_right, HIGH);
  digitalWrite(in2_right, LOW);
  analogWrite(enA_right, 0);
  // */

  /*  
  for(int i= 0; i<4; i++)
  {
    int speed = 255; 
    int time_milli = 2500;
    forward_constant(speed, time_milli);
    delay(500);

    int direction = 1; // 1 => right , 0 => left
    int turn_delay = 400;
    turn_constant(speed, turn_delay , direction);
    delay(1000);
  }
  exit(0);
  // */

}

void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    
    switch (c)
    {
      // LED Control
      case 'X':
        sprintf(str, "%c : LED ON\n", char(c));
        Serial.print(str);
        digitalWrite(ledPin, HIGH);
        break;

      case 'x':
        sprintf(str, "%c : LED OFF\n", char(c));
        Serial.print(str);
        digitalWrite(ledPin, LOW);
        break;
      
      case 's':
        sprintf(str, "%c : MOVE SQUARE\n", char(c));
        Serial.print(str);
        //move robot in a square shape
        move_square();   
        //forward();
        //delay(5000);    
        break;

      default:
        sprintf(str, "%c : Unrecognized byte!\n", char(c));
        Serial.print(str);      
        break;

    }
  }
}

void move_square()
{
  for(int i= 0; i<4; i++)
  {
    int speed = 255; 
    int time_milli = 2500;
    forward_constant(speed, time_milli);
    delay(500);

    // /*
    int direction = 1; // 1 => right , 0 => left
    int turn_delay = 400;
    turn_constant(speed, turn_delay , direction);
    delay(1000);
    // */
  }
}
