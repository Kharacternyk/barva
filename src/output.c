#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "output.h"


void set_bg(float value, struct color bg, struct color target,
            enum output_format fmt) {
    switch (fmt) {
    case TTY:
        bg = color_mean(bg, target, value);
        printf("\033]11;#%02X%02X%02X\007",
               bg.rgb[0], bg.rgb[1], bg.rgb[2]);
        fflush(stdout);
        break;
    case HEX:
        bg = color_mean(bg, target, value);
        printf("#%02X%02X%02X\n",
               bg.rgb[0], bg.rgb[1], bg.rgb[2]);
        fflush(stdout);
        break;
    case BYT:
        putchar(value * 255);
        fflush(stdout);
        break;
    }
}
