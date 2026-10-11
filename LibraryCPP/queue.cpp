#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue
{
    Vector* data;
    size_t size;
    size_t head;
    size_t capacity;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->capacity = 4;
    queue->data = vector_create();
    queue->head = 0;
    queue->size = 0;
    vector_resize(queue->data, queue->capacity);
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->data);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if(queue->size == queue->capacity)
    {
        size_t new_capacity = queue->capacity * 2;
        Vector* new_data = vector_create();
        vector_resize(new_data, new_capacity);
        for(size_t i = 0; i < queue->size; i++){
            vector_set(new_data, i, vector_get(queue->data, (queue->head + i) % queue->capacity));
        }
        vector_delete(queue->data);
        queue->capacity = new_capacity;
        queue->data = new_data;
        queue->head = 0;
    }
    size_t tail = (queue->head + queue->size) % queue->capacity;
    vector_set(queue->data, tail, data);
    queue->size++;
}

Data queue_get(const Queue *queue)
{
    if(queue_empty(queue)) throw std::out_of_range("queue empty");
    return vector_get(queue->data, queue->head);
}

void queue_remove(Queue *queue)
{
    if(queue_empty(queue)) throw std::out_of_range("queue empty");
    queue->head = (queue->head + 1) % queue->capacity;
    queue->size--;
}

bool queue_empty(const Queue *queue)
{
    return queue->size == 0;
}
