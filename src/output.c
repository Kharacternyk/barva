#include <stdio.h>

void update_render(float mean) {
    int brightness = 255 * (1 - mean);
    printf("\033]11;#FF%02X%02X\007", brightness, brightness);
    fflush(stdout);
}
