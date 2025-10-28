#include "queue.h"
#include <stdlib.h>
#include "vector.h"
struct Queue
{
    Vector* data;
    size_t front;
    size_t back;
    size_t count;
};

Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->data = vector_create();
    queue->front = 0;
    queue->back = 0;
    queue->count = 0;

    vector_resize(queue->data, 8);
    return queue;
}

void queue_delete(Queue* queue)
{
    vector_delete(queue->data);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (queue->count >= vector_size(queue->data)) {
        size_t old_size = vector_size(queue->data);
        size_t new_size = old_size * 2;

        Vector* new_data = vector_create();
        vector_resize(new_data, new_size);

        for (size_t i = 0; i < queue->count; i++) {
            size_t idx = (queue->front + i) % old_size;
            vector_set(new_data, i, vector_get(queue->data, idx));
        }

        vector_delete(queue->data);
        queue->data = new_data;
        queue->front = 0;
        queue->back = queue->count;
    }

    vector_set(queue->data, queue->back, data);
    queue->back = (queue->back + 1) % vector_size(queue->data);
    queue->count++;
}

Data queue_get(const Queue* queue)
{
    if (queue_empty(queue)) {
        return 0;
    }
    return vector_get(queue->data, queue->front);
}

void queue_remove(Queue* queue)
{
    if (!queue_empty(queue)) {
        queue->front = (queue->front + 1) % vector_size(queue->data);
        queue->count--;
    }
}

bool queue_empty(const Queue* queue)
{
    return queue->count == 0;
}