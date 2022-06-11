// Copy of https://titanwolf.org/Network/Articles/Article?AID=c06d53e1-6d8f-42f4-b9ea-e7dc8cf9441a#gsc.tab=0
// ... but how does one free this of Raspberry Pi magic, i.e. no "wiringPiI2CSetup" etc. ?!?!!


#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
 
 #define BH1750_ADDRESS              0x23   //SECOND ADDRESS 0x53
 #define BH1750_POWER_DOWN           0x00
 #define BH1750_POWER_ON             0x01
 #define BH1750_RESET                0x07
 #define BH1750_CONTINUE_H_RESOLUTION_MODE   0x10
 #define BH1750_CONTINUE_H_RESOLUTION_MOD2   0x11
 #define BH1750_CONTINUE_L_RESOLUTION_MODE   0x13
 #define BH1750_ONETIME_H_RESOLUTION_MODE    0x20
 #define BH1750_ONETIME_H_RESOLUTION_MOD2    0x21
 #define BH1750_ONETIME_L_RESOLUTION_MODE    0x23
 #define BH1750_MTREG                69 //DEFAULT 69 (31 - 254)
 #define BH1750_MODE_DIV             1  //MODE2 2
 #define BH1750_WAIT_TIME            150//ms
 
 int main(void) {

    int fd;
    int ret;

    unsigned char set_value[1];
    unsigned char result[2];

    int lData;

    fd = wiringPiI2CSetup(BH1750_ADDRESS);

    //Power On

    if((wiringPiI2CWrite(fd, BH1750_POWER_ON)) < 0) {
        printf("error: power on\n");
    }

    usleep(1000);

    //Set Configuration

    set_value[0] = BH1750_ONETIME_H_RESOLUTION_MODE;
    ret = write(fd, set_value, 1);
    if (ret < 0) {
        printf("error: set configuration value\n");
        return 1;
    } 

    usleep(BH1750_WAIT_TIME * 1000);

    //Get Value

    ret = read(fd, result, 2);

    if (ret < 0) {
        printf("error: read value\n");
        return 1;
    }

    lData = result[0] << 8;
    lData |= result[1];
    printf("Illuminace: %.2f\n lux", lData / 1.2 * (69 / BH1750_MTREG) / BH1750_MODE_DIV);
    return 0;
 }
