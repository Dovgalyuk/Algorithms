#include <stdlib.h>
#include "vector.h"
#include "queue.h"

const size_t shift = 5; // this is just for optimization (shifting every time is longer)

struct Queue
{
    Vector* vector;
    size_t head;
    size_t tail;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->vector = vector_create();
    vector_resize(queue->vector, 110);
    queue->head = 0;
    queue->tail = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{	
    Vector* q_vector = queue->vector;
    
    if (queue->tail >= vector_size(queue->vector) - 1 && queue->head == 0)
    {
        vector_resize(q_vector, vector_size(queue->vector) * 2);
    }
    else if (queue->tail + 1 == queue->head)
    {
        queue->head = 0;
        queue->tail = 0;
    }

    vector_set(q_vector, queue->tail, data);
    if (queue->tail == vector_size(queue->vector) - 1)
    {
        queue->tail = 0;
    }
    else
        queue->tail++;
}

Data queue_get(const Queue *queue)
{
    if (!queue_empty(queue))
    {
        return vector_get(queue->vector, queue->head);
    }
    else return NULL;
}

void queue_remove(Queue *queue)
{
    if (!queue_empty(queue))
    {
        if (queue->head >= vector_size(queue->vector) - 1)
        {
            queue->head = 0;
        }
        else queue->head++;
    }
}

bool queue_empty(const Queue *queue)
{
    return queue->tail == queue->head;
}
