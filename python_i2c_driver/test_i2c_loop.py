from smbus import SMBus
from time import sleep

bus = SMBus(1)  # indicates /dev/ic2-1
this_addr = int(input("Select address (integer):"))
assert type(this_addr==int)
print("Address selected:", this_addr)

while True:
    bus.write_byte(this_addr, False)
    sleep(1)
    bus.write_byte(this_addr, True)
    sleep(1)
