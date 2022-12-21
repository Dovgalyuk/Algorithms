#include "queue.h"
#include <iostream>
#include "vector.h"

struct Queue
{
    int id_r, id_l, el_amount;
    Vector* vec;
    Queue()
    {
        id_r = 0;
        id_l = 0;
        el_amount = 0;
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
    if (queue->id_r  == vector_size(queue->vec))
    {
        if (queue->id_l > 0)
            queue->id_r = 0;
        else
            vector_resize(queue->vec, vector_size(queue->vec) + 1);

    }
    else if (queue->id_r == queue->id_l)
    {
        vector_resize(queue->vec, vector_size(queue->vec) + queue->id_l);
        for (int i = 0; i < queue->id_l; i++)
        {
            queue->id_r--;
            vector_set(queue->vec, vector_size(queue->vec) - 1 - i, vector_get(queue->vec, queue->id_r));
            vector_set(queue->vec, queue->id_r, 0);

        }
    }
    vector_set(queue->vec, queue->id_r, data);
    queue->id_r++;
    queue->el_amount++;
}

Data queue_get(const Queue* queue)
{
    if (!queue_empty(queue))
    {   
        return vector_get(queue->vec, queue->id_l);
    }      
    else
    {
        return 0;
    }

}

void queue_remove(Queue* queue)
{
    if (queue_empty(queue))
    {
        return;
    }
    else
    {
        vector_set(queue->vec, queue->id_l, 0);
        queue->el_amount--;
        queue->id_l++;
        if (queue->id_l == vector_size(queue->vec))
            queue->id_l = 0;
    }
}

bool queue_empty(const Queue* queue)
{
        return queue->el_amount == 0;
}
