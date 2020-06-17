#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "output.h"


void set_bg(struct color bg, enum output_format fmt) {
    char str[8];

    switch (fmt) {
    case TTY:
        printf("\033]11;#%02X%02X%02X\007",
               bg.rgb[0], bg.rgb[1], bg.rgb[2]);
        fflush(stdout);
        break;
    case HEX:
        printf("#%02X%02X%02X\n",
               bg.rgb[0], bg.rgb[1], bg.rgb[2]);
        fflush(stdout);
        break;
    case BSPWM:
        sprintf(str, "#%02X%02X%02X",
                bg.rgb[0], bg.rgb[1], bg.rgb[2]);
        if (!(fork())) {
            execlp("bspc", "bpsc", "config", "normal_border_color", str, (char *)NULL);
            exit(0);
        } else {
            wait(NULL);
        }
        break;
    }
}
