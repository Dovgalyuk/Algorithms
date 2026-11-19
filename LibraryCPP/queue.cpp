#include "queue.h"
#include "vector.h"

using namespace std;

struct Queue
{
    Vector *buffer;
    size_t capacity;
    size_t head;   
    size_t count;  
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->buffer = vector_create();
    queue->capacity = 8;
    vector_resize(queue->buffer, queue->capacity);
    queue->head = 0;
    queue->count = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->buffer);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue->count == queue->capacity)
    {
        Vector *new_buffer = vector_create();
        vector_resize(new_buffer, queue->capacity * 2);
        for (size_t i = 0; i < queue->count; i++)
            vector_set(new_buffer, i,
                       vector_get(queue->buffer, (queue->head + i) % queue->capacity));
        vector_delete(queue->buffer);
        queue->buffer = new_buffer;
        queue->capacity *= 2;
        queue->head = 0;
    }

    vector_set(queue->buffer, (queue->head + queue->count) % queue->capacity, data);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->buffer, queue->head);
}

void queue_remove(Queue *queue)
{
    queue->head = (queue->head + 1) % queue->capacity;
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}
