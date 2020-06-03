#include "color.h"

struct cli_options {
    int queue_depth;
    struct color bg_color;
};

struct cli_options parse_cli_options(int argc, char *argv[]);
