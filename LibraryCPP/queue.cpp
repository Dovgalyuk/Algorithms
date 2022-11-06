#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *vector;
    size_t head;
    size_t rear;

    Queue() {
        vector = vector_create();
        vector_resize(vector, 2);
        head = 0;
        rear = 0;
    }
    ~Queue() {
        vector_delete(vector);
    }
};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    size_t size = vector_size(queue->vector);
    size_t rear = queue->rear;

    if(rear == size - 1) {
        vector_resize(queue->vector, size*2);
    }
    vector_set(queue->vector, rear, data);
    queue->rear++;
}

Data queue_get(const Queue *queue)
{
    if(!queue_empty(queue)) {
        Data value = vector_get(queue->vector, queue->head);
        return value;
    }
    return Data();
}

void queue_remove(Queue *queue)
{
    size_t size = vector_size(queue->vector);
    if(!queue_empty(queue) && queue->head <= size) {
        queue->head++;
    }
}

bool queue_empty(const Queue *queue)
{
    return (queue->rear == queue->head);
}