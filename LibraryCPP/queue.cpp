#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *buffer; 
    size_t head;    
    size_t count;   
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->buffer = vector_create();
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
    size_t ring_size = vector_size(queue->buffer);

    if (queue->count == ring_size) {
        size_t new_ring_size = (ring_size == 0) ? 1 : ring_size * 2;
        vector_resize(queue->buffer, new_ring_size);

        for (size_t i = 0; i < queue->head; i++) {
            vector_set(queue->buffer, ring_size + i, vector_get(queue->buffer, i));
        }
        ring_size = new_ring_size;
    }

    size_t tail = (queue->head + queue->count) % ring_size;
    vector_set(queue->buffer, tail, data);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    if (queue->count == 0) {
        return (Data)0;
    }
    return vector_get(queue->buffer, queue->head);
}

void queue_remove(Queue *queue)
{
    if (queue->count == 0) {
        return;
    }
    queue->head = (queue->head + 1) % vector_size(queue->buffer);
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}