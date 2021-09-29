#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* vector;
    size_t first;
    size_t last;
    size_t length = 0;

    Queue(): vector(vector_create()), first(0), last(-1), length(0) {}
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
    queue->first = 0;
    queue->last = size - 1;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue->length == vector_size(queue->vector)) {
        if (queue->first > 0) {
            queue_sort(queue);
        }
        vector_resize(queue->vector, vector_size(queue->vector) + 1);
    }
    queue->last++;
    queue->last %= vector_size(queue->vector);
    vector_set(queue->vector, queue->last, data);
    queue->length++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->first);
}

void queue_remove(Queue *queue)
{
    queue->first++;
    queue->first %= vector_size(queue->vector);
    if (queue->length > 0) {
        queue->length--;
    }
}

bool queue_empty(const Queue *queue)
{
    return !queue->length;
}
