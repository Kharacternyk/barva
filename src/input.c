#include <pulse/simple.h>
#include <pulse/error.h>
#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "errorcodes.h"

void get_samples(pa_simple *s, size_t bytes, int16_t *out) {
    int error = 0;
    pa_simple_read(
        s,
        out,
        bytes,
        &error
    );
    if (error) {
        fprintf(stderr, "PulseAudio error #%d: %s\n", error, pa_strerror(error));
        exit(PA_ERROR_CODE);
    }
}
