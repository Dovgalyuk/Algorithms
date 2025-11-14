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
    vector_delete(queue->data);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    size_t capacity = vector_size(queue->data);
    if (queue->count == capacity)
    {
        vector_resize(queue->data, queue->count * 2);

        Vector* temp = vector_create(); 
        vector_resize(temp, queue->count);

        for (size_t i = 0; i < queue->count; ++i) 
        { 
            size_t index = (queue->head + i) % capacity; 
            temp->data[i] = queue->data->data[index]; 
        }
        for (size_t i = 0; i < queue->count; ++i)
        {
            queue->data->data[i] = temp->data[i];
        }
        queue->head = 0; 
        vector_delete(temp);
    }
    size_t tail = (queue->head + queue->count) % capacity;
    queue->data->data[tail] = data;
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    return queue->data->data[queue->head];
}

void queue_remove(Queue *queue)
{
    size_t capacity = vector_size(queue->data);
    queue->head = (queue->head + 1) % capacity;
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}
