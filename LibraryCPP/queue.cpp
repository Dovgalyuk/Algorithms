#include "queue.h"

struct Queue
{
    size_t size = 0;
    size_t current_index = 0;
    Vector* vector = vector_create();
};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    if (queue != nullptr)
    {
        vector_delete(queue->vector);
        delete queue;
    }
}

void queue_insert(Queue* queue, Data data)
{
    if (queue->size == vector_size(queue->vector)) {
        size_t old_size = vector_size(queue->vector);
        size_t new_size = (old_size == 0) ? 1 : old_size * 2;
        Vector* temp = vector_copy(queue->vector);

        vector_resize(queue->vector, new_size);
        for (size_t i = 0; i < queue->size; i++) {
            vector_set(queue->vector, i, vector_get(temp, (queue->current_index + i) % old_size));
        }
        queue->current_index = 0;
    }
    vector_set(queue->vector, (queue->current_index + queue->size) % vector_size(queue->vector), data);
    queue->size++;
}

Data queue_get(const Queue *queue)
{
    if (queue != nullptr && !queue_empty(queue))
    {
        return vector_get(queue->vector, queue->current_index);
    }
    return (Data)0;
}

void queue_remove(Queue *queue)
{
    if (queue != nullptr && !queue_empty(queue))
    {
        queue->current_index++;
        queue->current_index = queue->current_index % vector_size(queue->vector);
        queue->size--;
    }
}

bool queue_empty(const Queue *queue)
{
    if (queue != nullptr && queue->size != 0)
        return false;
    return true;
}
