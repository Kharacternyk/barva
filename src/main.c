#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/pulseaudio.h>
#include <stdio.h>

int main() {
    pa_simple *s;
    pa_sample_spec ss;

    ss.format = PA_SAMPLE_S16NE;
    ss.channels = 1;
    ss.rate = 44100;

    int error = 0;

    char *sink_name = "alsa_output.pci-0000_01_02.0.analog-stereo.monitor";

    s = pa_simple_new(
        NULL,
        "barva",
        PA_STREAM_RECORD,
        sink_name,
        "barva",
        &ss,
        NULL,
        NULL,
        &error
    );
    printf("%d: %s\n", error, pa_strerror(error));

    for (;;) {
        int16_t buffer[8];
        pa_simple_read(
            s,
            buffer,
            sizeof(buffer),
            &error
        );
        printf("%d: %s\n", error, pa_strerror(error));

        for (int16_t *byte = buffer; byte < &buffer[sizeof(buffer) / sizeof(int16_t)]; ++byte) {
            printf("%d\n", *byte);
        }
    }
}
