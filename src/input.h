#include <pulse/simple.h>

/*
 * Audio samples per second.
 */
#define SAMPLE_RATE 1000
/*
 * Samples read per each get_samples() call.
 * SAMPLE_RATE / OUTPUT_RATE = update interval.
 */
#define OUTPUT_RATE 1

void get_samples(pa_simple *s, float *out);
pa_simple *get_pa_simple(const char *source_name);
