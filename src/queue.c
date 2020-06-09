#include <math.h>

#include "queue.h"

static int length(const struct queue *q) {
    return q->last - q->first + 1;
}

struct queue init_queue(float array[], int length) {
    struct queue q;
    q.first = array;
    q.last = &array[length-1];
    for (float *p = q.first; p <= q.last; ++p) {
        *p = 0;
    }
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
    /* Root mean square with Kahan summation */
    double sum = 0, c = 0, t, y;
    for (float *p = q->first; p <= q->last; ++p) {
        y = (*p) * (*p) - c;
        t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sqrt(sum / length(q));
}
