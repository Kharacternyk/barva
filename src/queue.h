struct queue {
    float *last;
    float *first;
};

struct queue init_queue(float array[], int length);
void queue_put(struct queue *q, float value);
float queue_average(const struct queue *q);
