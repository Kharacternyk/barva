#include <math.h>
#include <stdlib.h>

#include "queue.h"

/*
 * A value in range (0; 1).
 *
 * If W(n) is the weight of sample n (n=0 for the most recent sample), then
 * W(n+1) = W(n) * INERTIA
 *
 * VALUES LESS THAN 0.9999 CAN CAUSE FLICKER
 */
#define INERTIA 0.9999

/*
 * When W(n) < EPSILON, the sample n is ignored (as if W(n) = 0)
 * The smaller EPSILON is, the more memory is required for queue.
 */
#define EPSILON 1e-6

static int length(const struct queue *q) {
    return q->last - q->first + 1;
}

struct queue init_queue(void) {
    size_t size = log(EPSILON) / log(INERTIA);
    float *array = calloc(sizeof(float), size);

    struct queue q = {
        .first = array,
        .last = &array[size - 1],
        .entry = array,
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
    double weight = (1.0 - INERTIA) / (1.0 - pow(INERTIA, length(q)));
    double sum = 0, c = 0;
    for (float *p = q->entry - 1; p >= q->first; --p) {
        double y = (*p) * (*p) * weight - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
        weight *= INERTIA;
    }
    for (float *p = q->last; p >= q->entry; --p) {
        double y = (*p) * (*p) * weight - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
        weight *= INERTIA;
    }
    return sqrt(sum);
}
