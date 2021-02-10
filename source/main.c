#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "colors.h"
#include "battery.h"
#include "wifi.h"

#define x1b(x, xx)      printf("\x1b[%d;%dH", x, xx);
#define DIRECTORY       "/3ds/Battery-Percentage-Viewer/"

/**
 * @author Pavlos Efstathiou
 * @version 0.10 Pre Release
 */

void arrow( void ) {
    int pos = 0;
    const char* batteryPer = "Battery percentage";
    const char* exit = "Exit";
    const char* wifiStrength = "Wifi Strength";

    while (aptMainLoop()) {
        mcuHwcInit();
        hidScanInput();

        u32 kDown = hidKeysDown();

        if (kDown & KEY_DUP || kDown & KEY_CPAD_UP) {
            pos++;
            consoleClear();
        }
        else if (kDown & KEY_DDOWN || kDown & KEY_CPAD_DOWN) {
            pos--;
            consoleClear();
        }
        else if (kDown & KEY_DLEFT || kDown & KEY_CPAD_LEFT) {
            pos = 1;
            consoleClear();
        }
        else if (kDown & KEY_DRIGHT || kDown & KEY_CPAD_RIGHT) {
            pos = 0;
            consoleClear();
        }

        if (pos > 2) {
            sleep(0.2);
            pos = 0;
        }
        if (pos < 0)
            pos = 1;

        if (pos == 1) {
            printf("\x1b[0;0H %s  ", batteryPer);
            printf("\x1b[2;0H %s  ", wifiStrength);
            printf("\x1b[4;0H-> %s", exit);
        }
        if (pos == 2) {
            printf("\x1b[0;0H %s  ", batteryPer);
            printf("\x1b[2;0H-> %s", wifiStrength);
            printf("\x1b[4;0H %s  ", exit);
        }
        if (pos == 0) {
            printf("\x1b[0;0H-> %s", batteryPer);
            printf("\x1b[2;0H %s  ", wifiStrength);
            printf("\x1b[4;0H %s  ", exit);
        }

        if (pos == 1 && kDown & KEY_A)
            break;
        if (pos == 0 && kDown & KEY_A) {
            consoleClear();
            while (aptMainLoop()) {
                hidScanInput();

                u32 kDown = hidKeysDown();
                getBatteryPercentage();
                if (kDown & KEY_B || kDown & KEY_START) 
                    break;
            }
        }
        if (pos == 2 && kDown & KEY_A) {
            consoleClear();
            while (aptMainLoop()) {
                hidScanInput();

                u32 kDown = hidKeysDown();
                wifiStrengthFunc();
                if (kDown & KEY_B || kDown & KEY_START) 
                    break;
            }
        }
        if (kDown & KEY_B || kDown & KEY_START) 
            break;
        gfxFlushBuffers();
	    gfxSwapBuffers();
        gspWaitForVBlank();
    }
    mcuHwcExit();
    gfxExit();
}


int main() { //int argc, char **argv) {
    PrintConsole topScreen, bottomScreen;
    gfxInitDefault();
    consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);
    mkdir(DIRECTORY, 7777);
    consoleSelect(&topScreen);
    arrow();
    // The top screen has 30 rows and 50 columns
    //The bottom screen has 30 rows and 40 columns
	return 0;
}