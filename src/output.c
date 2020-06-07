#include <stdio.h>

#include "output.h"

void update_render(float mean, struct color bg, struct color target) {
    bg = color_in_between(bg, target, mean);
    printf(
        "\033]11;#%02X%02X%02X\007",
        bg.components[0],
        bg.components[1],
        bg.components[2]
    );
    fflush(stdout);
}
