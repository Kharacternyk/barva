#ifndef __output__
#define __output__

#include "color.h"

enum output_format {
    TTY, HEX, BYT
};

void set_bg(float value, struct color bg, struct color target,
            enum output_format fmt);

#endif
