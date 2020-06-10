#include <math.h>
#include <stdlib.h>

#include "queue.h"

/*
 * The smaller EPSILON is, the "smoother" is queue_mean().
 * The smaller EPSILON is, the more memory is required for queue.
 */
#define EPSILON 1e-6

static int length(const struct queue *q) {
    return q->last - q->first + 1;
}

struct queue init_queue(double inertia) {
    size_t length = log(EPSILON) / log(inertia);
    float *array = calloc(sizeof(float), length);

    struct queue q = {
        .first = array,
        .last = &array[length - 1],
        .inertia = inertia
    };
    return q;
}

void queue_put(struct queue *q, float values[], int values_length) {
    for (float *p = q->first; p <= q->last - values_length; ++p) {
        *p = *(p + values_length);
    }
    for (float *p = q->last - values_length + 1; p <= q->last; ++p) {
        *p = values[q->last - p];
    }
}

float queue_mean(const struct queue *q) {
    /* Weighted root mean square (RMS) with Kahan summation */
    double weight = (1.0 - q->inertia) / (1.0 - pow(q->inertia, length(q)));
    double sum = 0, c = 0, t, y;
    for (float *p = q->last; p >= q->first; --p) {
        y = (*p) * (*p) * weight - c;
        t = sum + y;
        c = (t - sum) - y;
        sum = t;
        weight *= q->inertia;
    }
    return sqrt(sum);
}
