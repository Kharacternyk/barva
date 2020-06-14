#include <stdio.h>

#include "output.h"

void set_bg(struct color bg, enum output_format fmt) {
    switch (fmt) {
    case TTY:
        printf("\033]11;#%02X%02X%02X\007",
               bg.rgb[0], bg.rgb[1], bg.rgb[2]);
        break;
    case HEX:
        printf("#%02X%02X%02X\n",
               bg.rgb[0], bg.rgb[1], bg.rgb[2]);
        break;
    }
    fflush(stdout);
}
