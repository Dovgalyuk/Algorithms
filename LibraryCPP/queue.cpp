#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector * vector;
    size_t first; 
    size_t sz; 
};

Queue *queue_create()
{
    Queue * queue = new Queue();
    queue->vector = vector_create();
    queue->first = 0;
    queue->sz = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if(queue->sz == vector_size(queue->vector)){
        Vector * vector = vector_create();
        vector_resize(vector, vector_size(queue->vector) * 2 + 1);
        for (int i = 0; i != queue->sz; i++){
            vector_set(vector, i, vector_get(queue->vector, (queue->first + i) % vector_size(queue->vector)));
        }
        vector_delete(queue->vector);
        queue->vector = vector;
        queue->first = 0;
    }
    vector_set(queue->vector, (queue->first + queue->sz + 1) % vector_size(queue->vector));
    queue->sz++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->first);
}

void queue_remove(Queue *queue)
{
    queue->first++;
    queue->sz--;
}

bool queue_empty(const Queue *queue)
{
    return queue->sz == 0;
}
