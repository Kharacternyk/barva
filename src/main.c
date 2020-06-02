#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/pulseaudio.h>
#include <stdio.h>
#include <math.h>

#include "input.h"

int main() {
    char *source_name = "alsa_output.pci-0000_01_02.0.analog-stereo.monitor";
    pa_simple *s = get_pa_simple(source_name);

    float average_square_sum = 0;
    long int chunks_processed = 0;
    int color = 0;
    for (;;) {
        float buffer[OUTPUT_RATE];
        get_samples(s, buffer);

        float square_sum = 0;
        for (
            float *sample = buffer;
            sample < &buffer[sizeof(buffer) / sizeof(float)];
            ++sample
        ) {
            square_sum += (*sample) * (*sample);
        }

        if (square_sum > average_square_sum && color < 255) {
            ++color;
        } else if (square_sum < average_square_sum && color > 0) {
            --color;
        }

        printf("%f:%f\n", square_sum, average_square_sum);

        char color_str[8];
        sprintf(color_str,"#FF%02X%02X", 255-color, 255-color);
        printf("\033]11;%s\007", color_str);
        fflush(stdout);

        average_square_sum =
            (average_square_sum * chunks_processed + square_sum) / (chunks_processed + 1);
        ++chunks_processed;
    }
}
