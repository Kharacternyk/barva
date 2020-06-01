#include <pulse/error.h>
#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "errorcodes.h"

static void check(int error) {
    if (error) {
        fprintf(stderr, "PulseAudio error #%d: %s\n", error, pa_strerror(error));
        exit(PA_ERROR_CODE);
    }
}

pa_simple *get_pa_simple(const char *source_name) {
    pa_simple *s;
    pa_sample_spec ss;

    ss.format = PA_SAMPLE_S16NE;
    ss.channels = 1;
    ss.rate = SAMPLE_RATE;

    int error = 0;
    s = pa_simple_new(
        NULL,
        "barva",
        PA_STREAM_RECORD,
        source_name,
        "barva",
        &ss,
        NULL,
        NULL,
        &error
    );
    check(error);
    return s;
}

void get_samples(pa_simple *s, int16_t *out) {
    int error = 0;
    pa_simple_read(
        s,
        out,
        OUTPUT_RATE * 2,
        &error
    );
    check(error);
}
