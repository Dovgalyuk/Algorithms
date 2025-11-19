#include "queue.h"
#include <stdexcept>

Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->vector = vector_create();
    queue->front = 0;
    queue->back = 0;
    queue->count = 0;
    vector_resize(queue->vector, 4); 
    return queue;
}

void queue_delete(Queue* queue)
{
    if (queue) {
        vector_delete(queue->vector);
        delete queue;
    }
}

void queue_insert(Queue* queue, Data data)
{
    if (!queue) return;
    
    if (queue->count >= vector_size(queue->vector)) {
        size_t old_capacity = vector_size(queue->vector);
        vector_resize(queue->vector, old_capacity * 2);
        
        if (queue->front > queue->back) {
            for (size_t i = 0; i < queue->back; ++i) {
                vector_set(queue->vector, old_capacity + i, vector_get(queue->vector, i));
            }
            queue->back = old_capacity + queue->back;
        }
    }
    
    vector_set(queue->vector, queue->back, data);
    queue->back = (queue->back + 1) % vector_size(queue->vector);
    queue->count++;
}

Data queue_get(const Queue* queue)
{
    if (!queue || queue_empty(queue)) {
        throw std::runtime_error("Queue is empty");
    }
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue* queue)
{
    if (!queue || queue_empty(queue)) return;
    
    queue->front = (queue->front + 1) % vector_size(queue->vector);
    queue->count--;
}

bool queue_empty(const Queue* queue)
{
    return !queue || queue->count == 0;
}