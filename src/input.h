#include <pulse/simple.h>

/*
 * Audio samples per second.
 */
#define SAMPLE_RATE 1000
/*
 * Samples read per each get_samples() call.
 * SAMPLE_RATE / OUTPUT_RATE = update interval.
 */
#define OUTPUT_RATE 100

void get_samples(pa_simple *, int16_t *);
pa_simple *get_pa_simple(const char *source_name);
