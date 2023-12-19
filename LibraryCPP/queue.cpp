#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* data;
    size_t head;
    size_t tail;
};

Queue *queue_create()
{
    Queue* tmp = new Queue;
    tmp->data = vector_create();
    tmp->head = tmp->tail = 0;
    return tmp;
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
    vector_delete(queue->data);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (vector_size(queue->data) <= queue->tail)
    {
        Vector* newData = vector_create();
        vector_resize(newData, (queue->tail + 1) * 2);
        size_t j = 0;
        for (size_t i = queue->head; i < queue->tail; i++, j++)
        {
            vector_set(newData, j, vector_get(queue->data, i));
        }

        queue->tail = j;
        queue->head = 0;
        vector_delete(queue->data);
        queue->data = newData;
    }
    vector_set(queue->data, queue->tail++, data);
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->data, queue->head);
}

void queue_remove(Queue *queue)
{
    queue->head++;
}

bool queue_empty(const Queue *queue)
{
    return (queue->tail - queue->head == 0);
}
