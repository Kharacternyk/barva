#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/pulseaudio.h>
#include <signal.h>

#include "input.h"
#include "output.h"
#include "queue.h"
#include "opts.h"

struct opts opts;
void restore_bg(int sig);

int main(int argc, char *argv[]) {
    opts = parse_opts(argc, argv);

    signal(SIGINT, restore_bg);
    signal(SIGTERM, restore_bg);

    pa_simple *s = get_pa_simple(opts.source);

    struct queue queue = init_queue(opts.inertia);

    for (;;) {
        float buffer[SAMPLE_CHUNK];
        get_samples(s, buffer);
        queue_put(&queue, buffer, SAMPLE_CHUNK);
        set_bg(color_mean(opts.bg, opts.target, queue_mean(&queue)), opts.output_format);
    }
}

void restore_bg(int sig) {
    if (opts.output_format == TTY) {
        set_bg(opts.bg, TTY);
    };
    exit(0);
}
