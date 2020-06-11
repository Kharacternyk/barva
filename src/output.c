#include <stdio.h>
#include <unistd.h>

#include "output.h"

void set_bg(struct color bg) {
    if (isatty(fileno(stdout))) {
        printf("\033]11;#%02X%02X%02X\007",
               bg.components[0], bg.components[1], bg.components[2]);
    } else {
        printf("#%02X%02X%02X\n",
               bg.components[0], bg.components[1], bg.components[2]);
    }
    fflush(stdout);
}
