#include "color.h"

struct opts {
    const char *source;
    double inertia;
    struct color bg;
    struct color target;
};

struct opts parse_opts(int argc, char *argv[]);
