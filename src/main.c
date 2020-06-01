#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/pulseaudio.h>
#include <stdio.h>

#include "input.h"

int main() {
    char *source_name = "alsa_output.pci-0000_01_02.0.analog-stereo.monitor";
    pa_simple *s = get_pa_simple(source_name);

    for (;;) {
        float buffer[OUTPUT_RATE];
        get_samples(s, buffer);

        float square_sum = 0;
        for (
            float *sample = buffer;
            sample < &buffer[sizeof(buffer) / sizeof(int16_t)];
            ++sample
        ) {
            square_sum += (*sample) * (*sample);
        }

        printf("value: %f\n", square_sum);

        /*
        int color = 255 - (square_sum >> 16);
        char color_str[8];
        sprintf(color_str,"#FF%02X%02X", color, color);
        printf("%s\n", color_str);
        printf("\033]11;%s\007", color_str);
        */
    }
}
