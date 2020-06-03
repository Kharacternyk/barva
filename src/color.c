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

void color_multiply(struct color *cp, float value) {
    for (int i = 0; i < 3; ++i) {
        cp->components[i] *= value;
    }
    overflow(cp);
}

void color_add(struct color *cp, int value) {
    for (int i = 0; i < 3; ++i) {
        cp->components[i] += value;
    }
    overflow(cp);
}
