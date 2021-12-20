#include "queue.h"


struct Queue
{
    Vector* vector;
    int first_index,last_index;
    bool is_empty;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->vector = vector_create();
    queue->last_index = -1;
    queue->first_index = 0;
    queue->is_empty = true;
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
        queue->last_index = 0;
    }
    if (queue->last_index == queue->first_index && queue->is_empty == false)
    {
        int shift = queue->last_index;
        Data* buffer = new Data[shift];
        for (int i = 0; i < shift; i++)
        {
            buffer[i] = vector_get(queue->vector,i);           
        }
        for (int i = queue->first_index; i < vector_size(queue->vector); i++)
        {
            vector_set(queue->vector,i - shift,vector_get(queue->vector,i));
        }
        for (int i = 0,j = vector_size(queue->vector) - shift; i < shift; i++,j++)
        {
            vector_set(queue->vector, j,buffer[i]);
        }
        queue->first_index = 0;
        queue->last_index = vector_size(queue->vector);
        vector_resize(queue->vector, queue->last_index * 2);
        delete[] buffer;
    }
    vector_set(queue->vector,queue->last_index,data);
    queue->is_empty = false;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector,queue->first_index);
}

void queue_remove(Queue *queue)
{
    if (queue->first_index == queue->last_index)
    {
        queue->is_empty = true;
    }
    queue->first_index++;
    if (queue->first_index == vector_size(queue->vector))
    {
        queue->first_index = 0;
    }
}

bool queue_empty(const Queue *queue)
{
    return queue->is_empty;
}
