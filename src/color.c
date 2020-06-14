#include "color.h"

/*
 * Returns a "mean" of two colors based on *value*.
 * *value* should be in [0; 1] where smaller values result in a color that is
 * closer to *c1* and vice versa.
 */
struct color color_mean(struct color c1, struct color c2, float value) {
    for (int i = 0; i < 3; ++i) {
        c1.rgb[i] += (c2.rgb[i] - c1.rgb[i]) * value;
    }
    return c1;
}
