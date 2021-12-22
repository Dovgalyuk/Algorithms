#include "queue.h"
#include "vector.h" 

struct Queue
{
    size_t first;
    size_t last;
    Vector* vector;
    Queue()
    {
        first = 0;
        last = 0;
        vector = vector_create();
    }

};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (vector_size(queue->vector) == 0)
        vector_resize(queue->vector, 1);

    if (queue->last >= vector_size(queue->vector) - 1 && queue->first == 0) 
    {
        vector_resize(queue->vector, vector_size(queue->vector) + 1);
    }

    if (queue->last + 1 == queue->first) 
    {
        Vector* new_vector = vector_create();
        vector_resize(new_vector, vector_size(queue->vector) +1);
        int j = 0;
        for (int i = queue->first; i < vector_size(queue->vector); i++) 
        {
            vector_set(new_vector, j, vector_get(queue->vector, i));
            j++;
        }
        for (int i = 0; i < queue->last; i++) 
        {
            vector_set(new_vector, j, vector_get(queue->vector, i));
            j++;
        }
        
        vector_delete(queue->vector);
        queue->vector = new_vector;
        queue->first = 0;
        queue->last = j;
    }
 
    vector_set(queue->vector, queue->last, data);
    
    if (queue->last == vector_size(queue->vector) - 1 && queue->first != 0)
    {
        queue->last = 0;
    }
    else
        queue->last++;
}
  
Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->first);
}

void queue_remove(Queue *queue)
{
    if (!queue_empty(queue))
        if (queue->first >= vector_size(queue->vector) - 1)
        {
            queue->first = 0;
        }
        else queue->first++;
}

bool queue_empty(const Queue *queue)
{
    return queue->first == queue->last;
}
