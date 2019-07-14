import lcddriver 
import time

I2C_BUS_DEVICE_NUMBER = 1
I2C_ADDRESS = 0x26

lcd = lcddriver.lcd(I2C_ADDRESS,I2C_BUS_DEVICE_NUMBER)

lcd.lcd_clear()

lcd.lcd_display_string("Testing l1", 1)
lcd.lcd_display_string("Testing l2", 2)

time.sleep(5)

lcd.lcd_backlight("off")
