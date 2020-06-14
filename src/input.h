#include <pulse/simple.h>

pa_simple *get_pa_simple(const char *source_name, size_t sample_rate);
void get_samples(pa_simple *s, size_t sample_size, float *out);
