#ifndef __color__
#define __color__

struct color {
    int components[3];
};

struct color color_in_between(struct color c1, struct color c2, float value);
#endif