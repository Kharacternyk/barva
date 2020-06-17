#include <stdint.h>

#include "color.h"
#include "output.h"

struct opts {
    const char *source;
    double fps;
    struct color bg;
    struct color target;
    enum output_format output_format;
};

struct opts parse_opts(int argc, char *argv[]);
