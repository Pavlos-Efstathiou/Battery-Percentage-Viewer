#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "colors.h"
#include "battery.h"

void getBatteryPercentage( void ) { 
    u8 batteryLevel;
    MCUHWC_GetBatteryLevel(&batteryLevel);
    int battLevel = batteryLevel;
    if (battLevel > 50) {
        printf("\x1b[0;0H");
        printf("Battery: ");
        green();
        printf("%d%%\n", battLevel);
        reset();
    }
    else if (battLevel <= 50 && battLevel > 25) {
        printf("\x1b[0;0H");
        printf("Battery: ");
        yellow();
        printf("%d%%\n", battLevel);
        reset();
    }
    else if (battLevel <= 25) {
        printf("\x1b[0;0H");
        printf("Battery: ");
        red();
        printf("%d%%\n", battLevel);
        reset();
    }
}