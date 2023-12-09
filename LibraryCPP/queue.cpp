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
    vector_resize(queue->data, ++queue->tail);
    vector_set(queue->data, queue->tail - 1, data);
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
