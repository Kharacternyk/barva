#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "opts.h"
#include "errorcodes.h"

static int parse_color(const char *str, void *out) {
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

    *(struct color *)out = c;
    return 0;
failure:
    return -1;
}

static int parse_double(const char *str, void *out) {
    double result;
    char *bad_char;
    result = strtod(str, &bad_char);
    if (str[0] == '\0' || *bad_char != '\0') {
        return -1;
    }
    *(double *)out = result;
    return 0;
}

static int parse_str(const char *str, void *out) {
    *(const char **)out = str;
    return 0;
}

static void parse_opt(const char *optname, void *optfield,
                      int (*parser)(const char *str, void *out)) {
    char *optval = getenv(optname);
    if (optval == NULL) {
        return;
    }
    if (parser(optval, optfield)) {
        fprintf(stderr, "Invalid value: %s=%s\n", optname, optval);
        exit(BAD_ARG_CODE);
    }
}

struct opts parse_opts(int argc, char *argv[]) {
    struct opts opts = {
        .source = NULL,
        .inertia = 0.9999,
        .bg = {{0, 0, 0}},
        .target = {{255, 255, 255}}
    };

    parse_opt("BARVA_SOURCE", &opts.source, parse_str);
    parse_opt("BARVA_INERTIA", &opts.inertia, parse_double);
    parse_opt("BARVA_BG", &opts.bg, parse_color);
    parse_opt("BARVA_TARGET", &opts.target, parse_color);

    return opts;
}
