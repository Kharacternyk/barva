#include <math.h>

#include "queue.h"

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
    float square_sum = 0;
    for (float *p = q->first; p <= q->last; ++p) {
        square_sum += (*p) * (*p);
    }
    return sqrt(square_sum / (q->last - q->first + 1));
}
