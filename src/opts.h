#include "color.h"
#include "output.h"

struct opts {
    const char *source;
    double inertia;
    struct color bg;
    struct color target;
    enum output_format output_format;
};

struct opts parse_opts(int argc, char *argv[]);
