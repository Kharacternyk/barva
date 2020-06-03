#include <stdio.h>

#include "output.h"

void update_render(float mean, struct color bg_color) {
    color_add(&bg_color, mean * 255);
    printf(
        "\033]11;#%02X%02X%02X\007",
        bg_color.components[0],
        bg_color.components[1],
        bg_color.components[2]
    );
    fflush(stdout);
}
