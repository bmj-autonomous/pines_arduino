#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
// LiquidCrystal_I2C lcd(0x27, 4, 5, 6, 0, 1, 2, 3, 7, POSITIVE);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
    lcd.begin(16,2);
    lcd.clear();


    for(int i = 0; i< 3; i++) {
        lcd.backlight();
        delay(250);
        lcd.noBacklight();
        delay(250);
    }
    lcd.backlight(); // finish with backlight on  

    lcd.print("hello, world");
    delay(2000);


    lcd.setCursor(0,0); //Start at character 4 on line 0
    lcd.print("Hello, world!");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("HI!YourDuino.com");
    delay(8000);  

}

void loop() {}