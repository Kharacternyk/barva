#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/pulseaudio.h>
#include <stdio.h>

#include "input.h"

int main() {
    char *source_name = "alsa_output.pci-0000_01_02.0.analog-stereo.monitor";
    pa_simple *s = get_pa_simple(source_name);

    for (;;) {
        int16_t buffer[OUTPUT_RATE];
        get_samples(s, buffer);

        int min = buffer[0], max = buffer[0];
        for (
            int16_t *sample = buffer + 1;
            sample < &buffer[sizeof(buffer) / sizeof(int16_t)];
            ++sample
        ) {
            if (*sample < min) {
                min = *sample;
            }
            if (*sample > max) {
                max = *sample;
            }
        }

        printf("amplitude: %d\n", max - min);
    }
}
