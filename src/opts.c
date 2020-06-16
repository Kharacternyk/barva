#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "opts.h"
#include "errorcodes.h"

static int parse_color(const char *str, void *out) {
    if (str == NULL || strlen(str) != 7 || str[0] != '#') {
        return -1;
    }
    ++str;

    struct color c;
    char rgb_str [3][3];
    for (int i = 0; i < 3; ++i) {
        rgb_str[i][0] = *str++;
        rgb_str[i][1] = *str++;
        rgb_str[i][2] = '\0';

        char *bad_char;
        c.rgb[i] = strtol(rgb_str[i], &bad_char, 16);
        if (*bad_char != '\0') {
            return -1;
        }
    }

    *(struct color *)out = c;
    return 0;
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

static int parse_output_format(const char *str, void *out) {
    if (strcasecmp(str, "TTY") == 0) {
        *(enum output_format *)out = TTY;
        return 0;
    }
    if (strcasecmp(str, "HEX") == 0) {
        *(enum output_format *)out = HEX;
        return 0;
    }
    return -1;
}

#ifdef UNSAFE_OPTS
static int parse_size_t(const char *str, void *out) {
    size_t result;
    char *bad_char;
    result = (size_t)strtol(str, &bad_char, 0);
    if (str[0] == '\0' || *bad_char != '\0') {
        return -1;
    }
    *(size_t *)out = result;
    return 0;
}
#endif

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
    int is_tty = isatty(fileno(stdout));
    struct opts opts = {
        .source = NULL,
        .fps = 60.0,
        .bg = {{0, 0, 0}},
        .target = {{255, 255, 255}},
        .output_format = is_tty ? TTY : HEX,
        .sample_rate = 44100,
        .inertia = 0.9999,
    };

    parse_opt("BARVA_SOURCE", &opts.source, parse_str);
    parse_opt("BARVA_FPS", &opts.fps, parse_double);
    parse_opt("BARVA_BG", &opts.bg, parse_color);
    parse_opt("BARVA_TARGET", &opts.target, parse_color);
    parse_opt("BARVA_OUTPUT_FORMAT", &opts.output_format, parse_output_format);

    /*
     * INERTIA and SAMPLE_RATE options are not changeable by default.
     * The reason is that misuse of these options may cause barva to
     * not enough smooth the transitions i.e. flicker. This can be
     * dangerous to flicker-sensitive people. The options are left
     * accessible to the developers so that they can try to improve
     * the default appearance of barva.
     *
     * DO NOT DEFINE UNSAFE_OPTS UNLESS YOU ARE SURE
     * THAT FLICKER CAN NOT CAUSE HARM TO YOUR HEALTH!
     */
#ifdef UNSAFE_OPTS
    parse_opt("BARVA_SAMPLE_RATE", &opts.sample_rate, parse_size_t);
    parse_opt("BARVA_INERTIA", &opts.inertia, parse_double);
#endif

    return opts;
}
