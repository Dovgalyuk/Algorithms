#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* q = nullptr;
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

        for (size_t i = 1; i < vector_size(queue->q); ++i) {
            vector_set(queue->q, i - 1, vector_get(queue->q, i));
        }
        vector_resize(queue->q, vector_size(queue->q) - 1);  
    }
}


bool queue_empty(const Queue* queue)
{
    return vector_size(queue->q) == 0;  
}