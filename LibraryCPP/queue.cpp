#include "queue.h"
#include <stdexcept>

struct Queue
{
    Vector* vector;
    size_t front;
    size_t back;
};

Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->vector = vector_create();
    queue->front = 0;
    queue->back = 0;
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
    
    size_t capacity = vector_size(queue->vector);
    
    size_t count = (queue->back >= queue->front) ? 
                   (queue->back - queue->front) : 
                   (capacity - queue->front + queue->back);
    
    if (count >= capacity - 1) {
        size_t old_capacity = capacity;
        vector_resize(queue->vector, old_capacity * 2);
        capacity = old_capacity * 2;
        
        if (queue->front > queue->back) {
            for (size_t i = 0; i < queue->back; ++i) {
                vector_set(queue->vector, old_capacity + i, vector_get(queue->vector, i));
            }
            queue->back = old_capacity + queue->back;
        }
    }
    
    vector_set(queue->vector, queue->back, data);
    queue->back = (queue->back + 1) % capacity;
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
    
    size_t capacity = vector_size(queue->vector);
    queue->front = (queue->front + 1) % capacity;
}

bool queue_empty(const Queue* queue)
{
    if (!queue) return true;
    return queue->front == queue->back;
}