#include <3ds.h>
#include <stdio.h>
#include <unistd.h>

#include "colors.h"
#include "wifi.h"

void wifiStrengthFunc( void ) {
    u8 wifi = osGetWifiStrength();
    int wifiStrength = wifi;
    //sleep(2);
    if (wifiStrength == 0) {
        printf("\x1b[0;0H");
        red();
        printf("Terrible WiFi connection or not connected to a network at all");
        reset();
    }
    else if (wifiStrength == 1) {
        printf("\x1b[0;0H");
        red();
        printf("Bad WiFi connection");
        reset();
    }
    else if (wifiStrength == 2) {
        printf("\x1b[0;0H");
        green();
        printf("Decent WiFi connection");
        reset();      
    }
    else if (wifiStrength == 3) {
        printf("\x1b[0;0H");
        green();
        printf("Really good WiFi connection");
        reset();     
    }
}