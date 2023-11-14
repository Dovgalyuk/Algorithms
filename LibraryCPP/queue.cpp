#include "queue.h"
#include "vector.h"

struct Queue
{
    ptrdiff_t Head;
    ptrdiff_t Rear;
    Vector* vector;

    Queue()
    {
        Head = -1;
        Rear = -1;
        vector = vector_create();
        vector_resize(vector, size_t(2));
    }
};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue_empty(queue))
    {
        queue->Head = 1;
        queue->Rear = 1;
    }

    else if (queue->Rear < 0 )
    {
        ptrdiff_t size = vector_size(queue->vector);

        Vector* new_vector;
        new_vector = vector_create();
        vector_resize(new_vector, size * 2);

        for (ptrdiff_t i = size * 2 - 1, j = size - 1 ; i >= size; i--, j--)
        {
            vector_set(new_vector, i, vector_get(queue->vector, j));
        }

        vector_delete(queue->vector);
        queue->vector = new_vector;

        queue->Head = size * 2 - 1;
        queue->Rear = queue->Head - size;
    }

    vector_set(queue->vector, queue->Rear, data);
    queue->Rear--;
}

Data queue_get(const Queue *queue)
{
    if (!queue_empty(queue)) return vector_get(queue->vector, queue->Head);

    else return Data();
}

void queue_remove(Queue *queue)
{
    size_t size = vector_size(queue->vector);

    auto head = queue->Head;

    if (!queue_empty(queue)) {
        head--;

        if (queue->Rear == head)
        {
            queue->Head = -1;
            queue->Rear = -1;

            //vector_delete(queue->vector); //
            //queue->vector = vector_create();
            //vector_resize(queue->vector, size_t(2));
        }

        else
        {
            queue->Head = head % size;
            /*if (size > 2) vector_resize(queue->vector, --size);
            --queue->Head;*/
        }
    }
    
}

bool queue_empty(const Queue *queue)
{
    return (queue->Head == -1 && queue->Rear == -1);
}
