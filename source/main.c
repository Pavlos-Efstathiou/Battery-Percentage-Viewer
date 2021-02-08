#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "colors.h"

void batterySelect( void ) {
    
    u8 batteryLevel;
    MCUHWC_GetBatteryLevel(&batteryLevel);
    int battLevel = batteryLevel;
    printf("\x1b[2;0H                                   ");
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

void arrow( void ) {
    int pos = 0;
    char* text0 = "Battery percentage\n";
    char* text1 = "Exit              \n";
    while (true) {
        mcuHwcInit();
        hidScanInput();

        u32 kDown = hidKeysDown();

        if (kDown & KEY_DUP) {
            pos++;
        }
        if (kDown & KEY_DDOWN) {
            pos--;
        }

        if (pos > 1)
            pos = 0;
        if (pos < 0)
            pos = 1;

        if (pos == 1) {
            printf("\x1b[0;0H %s\n", text0);
            printf("\x1b[2;0H-> %s\n", text1);
        }
        if (pos == 0) {
            printf("\x1b[0;0H-> %s\n", text0);
            printf("\x1b[2;0H %s\n", text1);
        }

        if (pos == 1 && kDown & KEY_A) {
            break;
        }
        if (pos == 0 && kDown & KEY_A) {
            consoleClear();
            while (true) {
                hidScanInput();

                u32 kDown = hidKeysDown();
                batterySelect();
                if (kDown & KEY_B) break;
            }
        }

        if (kDown & KEY_B) break;
    }
}


int main() { //int argc, char **argv) {
    PrintConsole topScreen, bottomScreen;

    gfxInitDefault();
    consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);

    consoleSelect(&topScreen);
    arrow();

    // while (aptMainLoop()) {
    //     hidScanInput();

    //     u32 kDown = hidKeysDown();
        

    //     if (kDown & KEY_START) break;

    //     // Flush and swap framebuffers
    //     gfxFlushBuffers();
	// 	gfxSwapBuffers();
	// 	//Wait for VBlank
	// 	gspWaitForVBlank();
    // }
    mcuHwcExit();
	gfxExit();
	return 0;
}