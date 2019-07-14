import lcddriver 
import time

lcd = lcddriver.lcd()

lcd.lcd_clear()

lcd.lcd_display_string("Test l1", 1)
lcd.lcd_display_string("Test l2", 2)

time.sleep(5)

lcd.lcd_backlight("off")
