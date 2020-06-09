struct queue {
    float *last;
    float *first;
};

struct queue init_queue(float array[], int length);
void queue_put(struct queue *q, float values[], int values_length);
float queue_mean(const struct queue *q);
