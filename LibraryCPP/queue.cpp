#include "queue.h"


struct Queue
{
    Vector* vector;
    int first_index,last_index;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->vector = vector_create();
    queue->last_index = -1;
    queue->first_index = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    queue->last_index++;
    if (vector_size(queue->vector) == queue->last_index)
    {
        vector_resize(queue->vector,queue->last_index * 2);
    }
    vector_set(queue->vector,queue->last_index,data);
}

Data queue_get(const Queue *queue)
{
    if (queue->first_index > queue->last_index)
    {
        return (Data)0;
    }
    return vector_get(queue->vector,queue->first_index);
}

void queue_remove(Queue *queue)
{
    queue->first_index++;
}

bool queue_empty(const Queue *queue)
{
    return queue->first_index > queue->last_index;
}
