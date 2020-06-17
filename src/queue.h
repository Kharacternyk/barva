/*
 * Structure:
 * [**************************]
 *  ^first     ^entry        ^last
 *
 * Entry points to the element that will be removed on the next push.
 * For example, after `queue_put(&q, [1, 2, 3], 3);` the same queue will
 * look like this:
 * [***********123************]
 *  ^first        ^entry     ^last
 */
struct queue {
    float *last;
    float *first;
    float *entry;
};

struct queue init_queue(void);
void queue_put(struct queue *q, float values[], int values_length);
float queue_mean(const struct queue *q);
