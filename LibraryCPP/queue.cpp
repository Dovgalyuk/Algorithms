#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* vector;  
    size_t  front;   
    size_t  count;   
};

Queue *queue_create()
{
    Queue* q = new Queue;
    q->vector = vector_create();
    q->front = 0;
    q->count = 0;
    return q;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{

    size_t capacity = vector_size(queue->vector);

    if (capacity == 0)
    {
        vector_resize(queue->vector, 1);
        capacity = 1;
    }
    else if (queue->count == capacity)
    {
        Vector* newVector = vector_create();
        vector_resize(newVector, capacity * 2);
        
        for (size_t i = 0; i < queue->count; i++) {
            Data val = vector_get(queue->vector, (queue->front + i) % capacity);
            vector_set(newVector, i, val);
        }
        
        vector_delete(queue->vector);
        queue->vector = newVector;
        queue->front = 0;
        capacity = capacity * 2; 
    }

    size_t pos = (queue->front + queue->count) % capacity;
    vector_set(queue->vector, pos, data);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue *queue)
{
    if (queue->count == 0)
        return; 

    queue->front = (queue->front + 1) % vector_size(queue->vector);
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    return (queue->count == 0);
}
