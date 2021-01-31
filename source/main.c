#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "colors.h"
#include "sound_bgr.h"

int main(int argc, char **argv) {
    u8 batteryLevel;

    gfxInitDefault();
	mcuHwcInit();
    consoleInit(GFX_TOP, NULL);

    MCUHWC_GetBatteryLevel(&batteryLevel);
    int battLevel = batteryLevel;
    if (battLevel > 50) {
        printf("\x1b[127;1m");
        printf("\x1b[0;0H");
        printf("Battery: ");
        green();
        printf("%d%%\n", battLevel);
        reset();
    }
    else if (battLevel <= 50 && battLevel > 25) {
        printf("\x1b[127;1m");
        printf("\x1b[0;0H");
        printf("Battery: ");
        yellow();
        printf("%d%%\n", battLevel);
        reset();
    }
    else if (battLevel <= 25) {
        printf("\x1b[127;1m");
        printf("\x1b[0;0H");
        printf("Battery: ");
        red();
        printf("%d%%\n", battLevel);
        reset();
    }

    gfxSetDoubleBuffering(GFX_BOTTOM, false);
    u8 *fb = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
    memcpy(fb, sound_bgr, sound_bgr_size);
    while (aptMainLoop()) {
        hidScanInput();

        u32 kDown = hidKeysDown();

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