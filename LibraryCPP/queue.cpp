#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* vector;
    size_t first;
    size_t last;
    size_t amount = 0;

    Queue(): vector(vector_create()), first(0), last(0), amount(0) {}
};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_sort(Queue* queue) {
    size_t size = vector_size(queue->vector);
    Data* new_data = new Data[size];
    for (int i = 0; i < size; ++i) {
        new_data[i] = vector_get(queue->vector, (i + queue->first) % size);
    }
    for (int i = 0; i < size; ++i) {
        vector_set(queue->vector, i, new_data[i]);
    }
    delete[] new_data;
    queue->last -= queue->first;
    queue->last += size;
    queue->last %= size;
    queue->first = 0;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue->amount == vector_size(queue->vector)) {
        if (queue->first > 0) {
            queue_sort(queue);
        }
        vector_resize(queue->vector, vector_size(queue->vector) + 1);
    }
    queue->last++;
    queue->last %= vector_size(queue->vector);
    vector_set(queue->vector, queue->last, data);
    queue->amount++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->first);
}

void queue_remove(Queue *queue)
{
    queue->first++;
    queue->first %= vector_size(queue->vector);
    if (queue->amount > 0) {
        queue->amount--;
    }
}

bool queue_empty(const Queue *queue)
{
    return !queue->amount;
}
