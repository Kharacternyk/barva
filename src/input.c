#include <pulse/error.h>
#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "errorcodes.h"

/*
 * PulseAudio will resample it for us if needed.
 *
 * DO NOT change it to the value native to your source,
 * because the algorithm used in queue_mean() yields
 * different visual results for different sample rates.
 *
 * VALUES BIGGER THAT 44100 MAY CAUSE FLICKER
 */
#define SAMPLE_RATE 44100

static void check(int error) {
    if (error) {
        fprintf(stderr, "PulseAudio error #%d: %s\n", error, pa_strerror(error));
        exit(PA_ERROR_CODE);
    }
}

size_t get_sample_chunk_size(double fps) {
    return SAMPLE_RATE / fps;
}

pa_simple *get_pa_simple(const char *source_name, size_t sample_chunk_size) {
    pa_simple *s;
    pa_buffer_attr ba = {
        .fragsize = sample_chunk_size,
        /* This magic value lets PulseAudio pick a sensible default for us. */
        .maxlength = (uint32_t) -1
    };
    pa_sample_spec ss = {
        .format = PA_SAMPLE_FLOAT32NE,
        .channels = 1,
        .rate = SAMPLE_RATE
    };

    int error = 0;
    s = pa_simple_new(NULL, "barva", PA_STREAM_RECORD, source_name, "barva",
                      &ss, NULL, &ba, &error);
    check(error);
    return s;
}

void get_samples(pa_simple *s, size_t sample_chunk_size, float *out) {
    int error = 0;
    pa_simple_read(s, out, sizeof(float) * sample_chunk_size, &error);
    check(error);
}
