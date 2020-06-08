#include <stdio.h>

#include "output.h"

void set_bg(struct color bg) {
    printf(
        "\033]11;#%02X%02X%02X\007",
        bg.components[0],
        bg.components[1],
        bg.components[2]
    );
    fflush(stdout);
}
