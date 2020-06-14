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

pa_simple *get_pa_simple(const char *source_name, size_t sample_rate) {
    pa_simple *s;
    pa_sample_spec ss;

    ss.format = PA_SAMPLE_FLOAT32NE;
    ss.channels = 1;
    ss.rate = sample_rate;

    int error = 0;
    s = pa_simple_new(NULL, "barva", PA_STREAM_RECORD, source_name, "barva",
                      &ss, NULL, NULL, &error);
    check(error);
    return s;
}

void get_samples(pa_simple *s, size_t sample_chunk, float *out) {
    int error = 0;
    pa_simple_read(
        s,
        out,
        /* sizeof(float) = 4, we're in trouble otherwise. */
        sample_chunk * sizeof(float),
        &error
    );
    check(error);
}
