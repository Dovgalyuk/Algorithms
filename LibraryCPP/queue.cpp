#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* data;
    size_t head;
    size_t count;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->data = vector_create();
    queue->head = 0;
    queue->count = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
    if (!queue) return;
    vector_delete(queue->data);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (!queue) return;
    size_t capacity = vector_size(queue->data);
    if (queue->count == capacity)
    {
        size_t new_capacity;
        if (capacity == 0) new_capacity = 1;
        else
            new_capacity = capacity * 2;
        vector_resize(queue->data, new_capacity);
        for (size_t i = 0; i < queue->head; ++i){
            vector_set(queue->data, capacity + i, vector_get(queue->data, i));
        }
        capacity = new_capacity;
    }
    size_t last_elem = (queue->head + queue->count) % capacity;
    vector_set(queue->data, last_elem, data);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    if (!queue || queue->count == 0) return Data(0);
    return vector_get(queue->data, queue->head);
}

void queue_remove(Queue *queue)
{
    if(!queue || queue->count == 0) return;
    queue->head = (queue->head + 1) % vector_size(queue->data);
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    if(!queue) return true;
    return queue->count == 0;
}
