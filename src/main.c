#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/pulseaudio.h>
#include <stdio.h>
#include <math.h>

#include "input.h"
#include "output.h"

#define QUEUE_DEPTH 20

int main() {
    char *source_name = "alsa_output.pci-0000_01_02.0.analog-stereo.monitor";
    pa_simple *s = get_pa_simple(source_name);

    float queue[QUEUE_DEPTH];
    for (float *p = queue; p < &queue[QUEUE_DEPTH]; ++p) {
        *p = 0;
    }
    float average_rms = 0;
    int color = 0;
    for (;;) {
        float buffer[SAMPLE_CHUNK];
        get_samples(s, buffer);

        float square_sum = 0;
        for (
            float *sample = buffer;
            sample < &buffer[sizeof(buffer) / sizeof(float)];
            ++sample
        ) {
            square_sum += (*sample) * (*sample);
        }
        float root_mean_square = sqrt(square_sum / SAMPLE_CHUNK);

        printf("%f:%f\n", root_mean_square, average_rms);
        update_render(average_rms);

        average_rms = 0;
        for (float *p = queue; p < &queue[QUEUE_DEPTH]; ++p) {
            average_rms += *p;
        }
        average_rms /= QUEUE_DEPTH;
        for (float *p = queue; p < &queue[QUEUE_DEPTH-1]; ++p) {
            *p = *(p+1);
        }
        queue[QUEUE_DEPTH-1] = root_mean_square;
    }
}
