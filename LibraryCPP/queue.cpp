#include "queue.h"
#include "vector.h"

struct Queue
{
    size_t front;
    size_t size; // сколько эл. в очереди =/= сколько элементов в векторе

    Vector* vector;
};

Queue *queue_create()
{
    Queue* queue = new Queue{0, 0, vector_create()};

    vector_resize(queue->vector, 2);

    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if(queue->size >= vector_size(queue->vector))
    {
        size_t oldBuffer = vector_size(queue->vector);

        Vector* vectorNew = vector_create();
        vector_resize(vectorNew, oldBuffer * 2);

        size_t oldFront = queue->front;

        for(size_t i = 0; i < queue->size; i++)
        {
            vector_set(vectorNew, i, vector_get(queue->vector, oldFront));

            oldFront = (oldFront + 1) % oldBuffer;
        }

        vector_delete(queue->vector);
        queue->vector = vectorNew;

        queue->front = 0;
    }

    size_t tail = (queue->front + queue->size) % vector_size(queue->vector);
    vector_set(queue->vector, tail, data);

    queue->size++;
}

Data queue_get(const Queue *queue)
{
    if(queue_empty(queue)){
        return (Data)0;
    }
    else{
        return vector_get(queue->vector, queue->front);
    }
}

void queue_remove(Queue *queue)
{
    if(queue_empty(queue)){
        return;
    }
    else{
        if(queue->front + 1 >= vector_size(queue->vector)){
            queue->front = 0;
        }else{
            queue->front = queue->front + 1;
        }
        queue->size = queue->size - 1;
    }
}

bool queue_empty(const Queue *queue)
{
    if(queue->size == 0){
        return true;
    }
    else{
        return false;
    }
}
