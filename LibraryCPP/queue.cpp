#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue
{
    Vector* vector;
    size_t head = 0;
    size_t tail = 0;
    size_t count = 0;
};

Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->vector = vector_create();
    vector_resize(queue->vector, 2); 
    return queue;
}

void queue_delete(Queue* queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (queue->count == vector_size(queue->vector))
    {
        
        Vector* new_vector = vector_create();
        vector_resize(new_vector, vector_size(queue->vector) * 2);
        
        
        for (size_t i = 0; i < queue->count; ++i)
        {
            vector_set(new_vector, i, vector_get(queue->vector, (queue->head + i) % vector_size(queue->vector)));
        }
        
        
        Vector* old_vector = queue->vector;
        queue->vector = new_vector;
        queue->head = 0;
        queue->tail = queue->count;
        vector_delete(old_vector);
    }
    
    vector_set(queue->vector, queue->tail, data);
    queue->tail = (queue->tail + 1) % vector_size(queue->vector);
    queue->count++;
}

Data queue_get(const Queue* queue)
{
    if (queue_empty(queue))
        throw std::runtime_error("Queue is empty");
    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue* queue)
{
    if (queue_empty(queue))
        throw std::runtime_error("Queue is empty");
    queue->head = (queue->head + 1) % vector_size(queue->vector);
    queue->count--;
}

bool queue_empty(const Queue* queue)
{
    return queue->count == 0;
}