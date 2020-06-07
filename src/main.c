#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/pulseaudio.h>
#include <stdio.h>
#include <math.h>

#include "input.h"
#include "output.h"
#include "queue.h"
#include "cli.h"

int main(int argc, char* argv[]) {
    struct opts opts = parse_opts(argc, argv);

    char *source_name = "alsa_output.pci-0000_01_02.0.analog-stereo.monitor";
    pa_simple *s = get_pa_simple(source_name);

    float buffer[opts.inertia];
    struct queue queue = init_queue(buffer, opts.inertia);

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
        update_render(queue_average(&queue), opts.bg);
    }
}
