struct queue {
    float *last;
    float *first;
    double inertia;
};

struct queue init_queue(double inertia);
void queue_put(struct queue *q, float values[], int values_length);
float queue_mean(const struct queue *q);
