#include "input.h"
#include "opts.h"
#include "output.h"
#include "queue.h"
#include <pulse/error.h>
#include <pulse/pulseaudio.h>
#include <pulse/simple.h>
#include <signal.h>

static struct opts opts;
static void restore_bg(int sig);

int main(int argc, char *argv[]) {
    opts = parse_opts(argc, argv);
    const size_t sample_chunk_size = get_sample_chunk_size(opts.fps);

    signal(SIGINT, restore_bg);
    signal(SIGTERM, restore_bg);

    pa_simple *s = get_pa_simple(opts.source, sample_chunk_size);

    struct queue queue = init_queue();

    for (;;) {
        float buffer[sample_chunk_size];
        get_samples(s, sample_chunk_size, buffer);
        queue_put(&queue, buffer, sample_chunk_size);
        set_bg(queue_mean(&queue), opts.bg, opts.target, opts.output_format);
    }
}

static void restore_bg(int sig) {
    set_bg(0, opts.bg, opts.target, opts.output_format);
    exit(0);
}
