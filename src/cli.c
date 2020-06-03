#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "errorcodes.h"

static struct color parse_hex_color(const char *str) {
    if (str == NULL) {
        goto failure;
    }

    str = strstr(str, "#");
    if (str == NULL || strlen(str) < 7) {
        goto failure;
    }
    ++str;

    struct color c;
    char components_str [3][3];
    for (int i = 0; i < 3; ++i) {
        components_str[i][0] = *str++;
        components_str[i][1] = *str++;
        components_str[i][2] = '\0';

        char *bad_char;
        c.components[i] = strtol(components_str[i], &bad_char, 16);
        if (*bad_char != '\0') {
            goto failure;
        }
    }

    return c;

failure:
    fprintf(stderr, "expected valid hex color\n");
    exit(BAD_ARG_CODE);
}

static int parse_int(const char *str) {
    int result;
    char *bad_char;
    result = strtol(str, &bad_char, 10);
    if (str[0] == '\0' || *bad_char != '\0') {
        fprintf(stderr, "expected valid integer\n");
        exit(BAD_ARG_CODE);
    }
    return result;
}

struct cli_options parse_cli_options(int argc, char *argv[]) {
    struct cli_options opts = {
        20,
        {0, 0, 0}
    };

    switch (argc) {
    default:
    case 3:
        opts.bg_color = parse_hex_color(argv[2]);
    case 2:
        opts.queue_depth = parse_int(argv[1]);
    case 1:
        break;
    }

    return opts;
}
