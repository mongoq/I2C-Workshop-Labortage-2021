#!/bin/bash

sudo i2cset -y 10 0x23 0x01 c
 sleep 1

sudo i2cset -y 10 0x23 0x20 c
 sleep 1

TMP=$(sudo i2cget -y 10 0x23 0x00 w)
 MSB="0x$(echo $TMP | cut -c 5-6)"
 LSB="0x$(echo $TMP | cut -c 3-4)"
 IL=$(((MSB<<8)|LSB))

LC_NUMERIC=C;
printf "Illuminance: %.2f lx\n" $(echo "scale=2;$IL/1.2" | bc)

exit 0
