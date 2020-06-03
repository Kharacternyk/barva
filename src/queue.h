struct queue {
    float *last;
    float *first;
};

void queue_put(struct queue *q, float value);
float queue_average(struct queue *q);
