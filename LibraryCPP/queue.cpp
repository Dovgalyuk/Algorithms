#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* q;
};


Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->q = vector_create();
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

    return vector_get(queue->q, 0);
}


void queue_remove(Queue* queue)
{
    if (!queue_empty(queue)) {

        int vih = 0;
        vih = (vih+1)%vector_size(queue->q);
        vector_resize(queue->q, vector_size(queue->q) - 1);
    }
}


bool queue_empty(const Queue* queue)
{
    return vector_size(queue->q) == 0;  
}


