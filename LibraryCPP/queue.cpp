#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* vector;
    size_t offset;
    size_t last;
    const size_t max_offset = 10;

    Queue(): vector(vector_create()), offset(0), last(0) {}
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

void queue_insert(Queue *queue, Data data)
{
    if (queue->last == queue->offset) {
        size_t new_size = vector_size(queue->vector) + 1;
        queue->last = vector_size(queue->vector);
        if (queue->offset > 0) {
            Data* new_data = new Data[new_size];
            vector_data_copy(queue->vector, new_data, vector_size(queue->vector) - queue->offset, queue->offset);
            vector_data_copy(queue->vector, new_data, queue->offset, 0, vector_size(queue->vector) - queue->offset);
            vector_set_data(queue->vector, new_data, new_size);
            queue->offset = 0;
        } else {
            vector_resize(queue->vector, new_size);
        }
    }
    vector_set(queue->vector, queue->last, data);
    queue->last++;
    queue->last %= vector_size(queue->vector);
    queue->offset %= vector_size(queue->vector);
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->offset);
}

void queue_remove(Queue *queue)
{
    queue->offset++;
}

bool queue_empty(const Queue *queue)
{
    return (vector_size(queue->vector) - queue->offset) <= 0;
}
