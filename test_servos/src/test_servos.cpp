#include <Arduino.h>
#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

const int PIN_SERVO1 = 3;
const int PIN_SERVO2 = 4;
const int PIN_SERVO3 = 5;
int position = 0;

void setup()
{
  servo1.attach(PIN_SERVO1);
  servo1.write(180);

  servo2.attach(PIN_SERVO2);
  servo2.write(180);

  servo3.attach(PIN_SERVO3);
  servo3.write(180);
}

void loop()
{
  for(position=0; position < 180; position += 1) {
    servo1.write(position);
    servo2.write(position);
    servo3.write(position);
    delay(10);
  }
  for(position=180; position > 1 ; position -= 1) {
    servo1.write(position);
    servo2.write(position);
    servo3.write(position);
    delay(10);
  }
}