import lcddriver 
import time

#I2C_BUS_DEVICE_NUMBER = 1
#I2C_ADDRESS = 0x26

lcd1 = lcddriver.lcd(0x27,1)
lcd2 = lcddriver.lcd(0x26,1)

lcd1.lcd_clear()
lcd2.lcd_clear()

lcd1.lcd_display_string("Testing LCD1 A", 1)
lcd1.lcd_display_string("Testing LCD1 B", 2)

lcd2.lcd_display_string("Testing LCD2 A", 1)
lcd2.lcd_display_string("Testing LCD2 B", 2)

#time.sleep(5)

#lcd2.lcd_backlight("off")
