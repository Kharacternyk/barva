#include "color.h"

struct color color_in_between(struct color c1, struct color c2, float value) {
    for (int i = 0; i < 3; ++i) {
        c1.components[i] += (c2.components[i] - c1.components[i]) * value;
    }
    return c1;
}
