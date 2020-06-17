#ifndef __output__
#define __output__

#include "color.h"

enum output_format {
    TTY, HEX, BSPWM
};

void set_bg(struct color bg, enum output_format fmt);

#endif
