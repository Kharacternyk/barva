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
    size_t size = log(EPSILON) / log(inertia);
    float *array = calloc(sizeof(float), size);

    struct queue q = {
        .first = array,
        .last = &array[size - 1],
        .entry = array,
        .inertia = inertia
    };
    return q;
}

void queue_put(struct queue *q, float values[], int values_length) {
    for (int i = 0; i < values_length; ++i) {
        *(q->entry++) = values[i];
        if (q->entry > q->last) {
            q->entry = q->first;
        }
    }
}

float queue_mean(const struct queue *q) {
    /* Weighted root mean square (RMS) with Kahan summation */
    double weight = (1.0 - q->inertia) / (1.0 - pow(q->inertia, length(q)));
    double sum = 0, c = 0;
    for (float *p = q->entry - 1; p >= q->first; --p) {
        double y = (*p) * (*p) * weight - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
        weight *= q->inertia;
    }
    for (float *p = q->last; p >= q->entry; --p) {
        double y = (*p) * (*p) * weight - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
        weight *= q->inertia;
    }
    return sqrt(sum);
}
