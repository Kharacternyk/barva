#include "queue.h"

void queue_put(struct queue *q, float value) {
    for (float *p = q->first; p < q->last; ++p) {
        *p = *(p+1);
    }
    *(q->last) = value;
}

float queue_average(struct queue *q) {
    float average = 0;
    for (float *p = q->first; p <= q->last; ++p) {
        average += *p;
    }
    average /= (1 + q->last - q->first);
    return average;
}
