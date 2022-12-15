#include "queue.h"
#include "vector.h"

struct Queue
{
    int id;
    Vector* vec;
    Queue()
    {
        id = 0;
        vec = vector_create();
        vector_resize(vec, 1);
    }
};

Queue* queue_create()
{
    return new Queue();
}

void queue_delete(Queue* queue)
{
    vector_delete(queue->vec);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    vector_set(queue->vec, queue->id, data);
    queue->id++;
    vector_resize(queue->vec, vector_size(queue->vec)+1);
    
}

Data queue_get(const Queue* queue)
{
    if (vector_get(queue->vec, 0))
        return vector_get(queue->vec, 0);
    else
        return 0;
}

void queue_remove(Queue* queue)
{
    for (int i = 0; i <= queue->id; i++)
    {
        vector_set(queue->vec, i, vector_get(queue->vec, i + 1));
    }
    queue->id--;
}

bool queue_empty(const Queue* queue)
{
    if (queue->id == 0)
        return true;
    else
        return false;

}
