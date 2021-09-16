#include "queue.h"
#include "vector.cpp"

struct Queue
{
    Vector* vector;
    size_t offset;
    const size_t max_offset = 10;

    Queue(): vector(vector_create()), offset(0) {}
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
    size_t index = vector_size(queue->vector);
    vector_resize(queue->vector, index + 1);
    vector_set(queue->vector, index, data);
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->offset);
}

void queue_remove(Queue *queue)
{
    queue->offset++;
    if (queue->offset > queue->max_offset) {
        size_t new_size = queue->offset + vector_size(queue->vector) - 1;
        if (new_size < 0)
            return;
        Data* new_data = new Data[new_size];
        queue->vector->data_copy(new_data, new_size, queue->offset);
        vector_resize(queue->vector, new_size);
        vector_delete(queue->vector);
        queue->vector = vector_create();
        queue->offset = 0;
    }
}

bool queue_empty(const Queue *queue)
{
    return (vector_size(queue->vector) - queue->offset) == 0;
}
