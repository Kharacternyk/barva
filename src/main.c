#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/pulseaudio.h>
#include <stdio.h>
#include <math.h>

#include "input.h"
#include "output.h"
#include "queue.h"

#define QUEUE_DEPTH 20

int main() {
    char *source_name = "alsa_output.pci-0000_01_02.0.analog-stereo.monitor";
    pa_simple *s = get_pa_simple(source_name);

    float buffer[QUEUE_DEPTH];
    struct queue queue = init_queue(buffer, QUEUE_DEPTH);

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
        queue_put(&queue, sqrt(square_sum / SAMPLE_CHUNK));
        update_render(queue_average(&queue));
    }
}
