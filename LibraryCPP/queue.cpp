#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* q;
    size_t nach;
};


Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->q = vector_create();
    queue->nach = 0;
    return queue;
}


void queue_delete(Queue* queue)
{
    vector_delete(queue->q);
    delete queue;
}


void queue_insert(Queue* queue, Data data)
{
    vector_resize(queue->q, vector_size(queue->q) + 1);  
    vector_set(queue->q, vector_size(queue->q) - 1, data);  
}


Data queue_get(const Queue* queue)
{
    return vector_get(queue->q, queue->nach);
}


void queue_remove(Queue* queue)
{
    if (!queue_empty(queue)){
        queue->nach++;
        if(queue->nach == vector_size(queue->q)){
            queue->nach = 0;
            vector_resize(queue->q,0);
        }
    }
}


bool queue_empty(const Queue* queue)
{
    return queue->nach == vector_size(queue->q);
}


