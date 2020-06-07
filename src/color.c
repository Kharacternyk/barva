#include "color.h"

static void overflow(struct color *cp) {
    for (int i = 0; i < 3; ++i) {
        if (cp->components[i] > 255) {
            cp->components[i] = 255;
        }
        if (cp->components[i] < 0) {
            cp->components[i] = 0;
        }
    }
}

struct color color_in_between(struct color c1, struct color c2, float value) {
    for (int i = 0; i < 3; ++i) {
        c1.components[i] += (c2.components[i] - c1.components[i]) * value;
    }
    overflow(&c1);
    return c1;
}
