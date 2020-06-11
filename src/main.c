#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/pulseaudio.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

#include "input.h"
#include "output.h"
#include "queue.h"
#include "opts.h"

struct color initial_bg;
enum output_format fmt;
void restore_bg(int sig);

int main(int argc, char *argv[]) {
    struct opts opts = parse_opts(argc, argv);

    fmt = isatty(fileno(stdout)) ? TTY : HEX;

    initial_bg = opts.bg;
    signal(SIGINT, restore_bg);
    signal(SIGTERM, restore_bg);

    pa_simple *s = get_pa_simple(opts.source);

    struct queue queue = init_queue(opts.inertia);

    for (;;) {
        float buffer[SAMPLE_CHUNK];
        get_samples(s, buffer);
        queue_put(&queue, buffer, SAMPLE_CHUNK);
        set_bg(color_mean(opts.bg, opts.target, queue_mean(&queue)), fmt);
    }
}

void restore_bg(int sig) {
    if (fmt == TTY) {
        set_bg(initial_bg, TTY);
    };
    exit(0);
}
