#ifndef __color__
#define __color__

struct color {
    int components[3];
};

void color_multiply(struct color *cp, float value);
void color_add(struct color *cp, int value);
#endif
