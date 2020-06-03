#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "errorcodes.h"

struct cli_options parse_cli_options(int argc, char *argv[]) {
    struct cli_options opts;
    opts.queue_depth = 20;
    if (argc > 1) {
        char *end;
        opts.queue_depth = strtol(argv[1], &end, 10);
        if (argv[1][0] == '\0' || *end != '\0') {
            fprintf(stderr, "QUEUE_DEPTH: expected valid integer\n");
            exit(BAD_ARG_CODE);
        }
    }
    return opts;
}
