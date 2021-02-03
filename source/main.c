#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include "colors.h"

#define TRUE "true"
#define FALSE "false"

int pos = 0;
char* text1 = "\x1b[0;0HBattery percentage";
char* text2 = "\x1b[0;0HExit";

void selector(int textNum) {
    char arrow[6];
    int textSize = 1;

    if (pos > textSize)
        pos = textSize;
    if (pos < 0) 
        pos = 0;

    if ( (textNum == 0) || (textNum == 1) )
        strncpy(arrow, TRUE, sizeof(arrow));
    else
        strncpy(arrow, FALSE, sizeof(arrow));

    if (strcmp(arrow, TRUE) == 0)
        strncpy(arrow, "->", sizeof(arrow));
    if (strcmp(arrow, TRUE) != 0)
        strncpy(arrow, "->", sizeof(arrow));

    if (textNum == 0)
        printf("%s %s", arrow, *text1);
    if (textNum == 1)
        printf("%s %s", arrow, *text2);
}
void selector( int );
void batterySelect() {
    PrintConsole topScreen, bottomScreen;
    u8 batteryLevel;
    MCUHWC_GetBatteryLevel(&batteryLevel);
    int battLevel = batteryLevel;
    if (battLevel > 50) {
        consoleSelect(&topScreen);
        printf("\x1b[0;0H");
        printf("Battery: ");
        green();
        printf("%d%%\n", battLevel);
        reset();
    }
    else if (battLevel <= 50 && battLevel > 25) {
        consoleSelect(&topScreen);
        printf("\x1b[0;0H");
        printf("Battery: ");
        yellow();
        printf("%d%%\n", battLevel);
        reset();
    }
    else if (battLevel <= 25) {
        consoleSelect(&topScreen);
        printf("\x1b[0;0H");
        printf("Battery: ");
        red();
        printf("%d%%\n", battLevel);
        reset();
    }
};
int main(int argc, char **argv) {
    PrintConsole topScreen, bottomScreen;

    gfxInitDefault();
	mcuHwcInit();
    consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);

    while (aptMainLoop()) {

        hidScanInput();

        u32 kDown = hidKeysDown();
        selector(0);
        selector(1);
        if (kDown & KEY_CPAD_UP) {
            pos++;
        }
        if (kDown & KEY_CPAD_DOWN) {
            pos--;
        }

        if (kDown & KEY_START) break;

        // Flush and swap framebuffers
        gfxFlushBuffers();
		gfxSwapBuffers();
		//Wait for VBlank
		gspWaitForVBlank();
    }
	mcuHwcExit();
	gfxExit();
	return 0;
}