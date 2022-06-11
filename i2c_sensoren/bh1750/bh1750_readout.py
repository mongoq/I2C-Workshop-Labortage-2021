#!/usr/bin/python

import time
import smbus
import decimal
bus = smbus.SMBus(10)
addr = 0x23
data = bus.read_i2c_block_data(addr,0x11)
lux2 = str((data[1] + (256 * data[0])) / 1.2)
lux = decimal.Decimal(lux2).quantize(decimal.Decimal('.01'), rounding=decimal.ROUND_UP)
outlux = str(lux)
print outlux
