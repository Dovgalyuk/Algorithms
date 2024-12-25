#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *vector;
    size_t first;
    size_t size;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->first = 0;
    queue->size = 0;
    queue->vector = vector_create();

    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if(queue->size + 1 > vector_size(queue->vector))
    {
        vector_resize(queue->vector, vector_size(queue->vector) + 1);
        if(queue->first != 0)
        {
            for(size_t i = vector_size(queue->vector) - 1; i > queue->first; i--)
            {
                vector_set(queue->vector, i, vector_get(queue->vector, i - 1));
            }
            queue->first++;
        }
    }
    size_t last = (queue->first + queue->size) % vector_size(queue->vector);
    vector_set(queue->vector, last, data);
    queue->size++;
}

Data queue_get(const Queue *queue)
{
   return vector_get(queue->vector, queue->first);
}

void queue_remove(Queue *queue)
{
    if(!queue_empty(queue))
    {
        queue->size--;
        queue->first = (queue->first + 1) % vector_size(queue->vector);
    }
}

bool queue_empty(const Queue *queue)
{
    if(queue->size == 0)
        return true;
        
    return false;
}
