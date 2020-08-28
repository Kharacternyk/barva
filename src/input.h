#include <pulse/simple.h>

size_t get_sample_chunk_size(double fps);
pa_simple *get_pa_simple(const char *source_name, size_t sample_chunk_size);
void get_samples(pa_simple *s, size_t sample_chunk_size, float *out);
