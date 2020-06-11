#include "color.h"

enum output_format {
    TTY, HEX
};

void set_bg(struct color bg, enum output_format fmt);
