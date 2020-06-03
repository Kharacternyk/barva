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

void queue_put(struct queue *q, float value) {
    for (float *p = q->first; p < q->last; ++p) {
        *p = *(p+1);
    }
    *(q->last) = value;
}

float queue_average(const struct queue *q) {
    float average = 0;
    for (float *p = q->first; p <= q->last; ++p) {
        average += *p;
    }
    average /= (1 + q->last - q->first);
    return average;
}
