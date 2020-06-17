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
    const size_t sample_chunk = opts.sample_rate / opts.fps;

    signal(SIGINT, restore_bg);
    signal(SIGTERM, restore_bg);

    pa_simple *s = get_pa_simple(opts.source, opts.sample_rate);

    struct queue queue = init_queue(opts.inertia);

    for (;;) {
        float buffer[sample_chunk];
        get_samples(s, sample_chunk, buffer);
        queue_put(&queue, buffer, sample_chunk);
        set_bg(color_mean(opts.bg, opts.target, queue_mean(&queue)), opts.output_format);
    }
}

void restore_bg(int sig) {
    set_bg(opts.bg, opts.output_format);
    exit(0);
}
