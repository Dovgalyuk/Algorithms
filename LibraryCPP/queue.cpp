#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue
{
    Vector *data;
    size_t currentIndex;
    size_t nextIndex;
    size_t count;
};

Queue *queue_create()
{
    Queue *myQueue = new Queue;
    myQueue->data = vector_create();
    myQueue->currentIndex = 0;
    myQueue->nextIndex = 0;
    myQueue->count = 0;

    return myQueue;
}

void queue_delete(Queue *queue)
{
    if (queue == nullptr)
        return;

    vector_delete(queue->data);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue == nullptr || queue->data == nullptr)
    {
        throw std::out_of_range("Queue is empty");
    }

    size_t capacity = vector_size(queue->data);

    if (queue->count == capacity)
    {
        Vector *newVector = vector_create();

        size_t newCapacity = capacity == 0 ? 1 : capacity * 2;

        vector_resize(newVector, newCapacity);

        for (size_t i = 0; i < queue->count; i++)
        {
            size_t oldIndex = (queue->currentIndex + i) % capacity;

            Data value = vector_get(queue->data, oldIndex);

            vector_set(newVector, i, value);
        }

        vector_delete(queue->data);

        queue->data = newVector;
        queue->currentIndex = 0;
        queue->nextIndex = queue->count;
    }

    vector_set(queue->data, queue->nextIndex, data);

    queue->nextIndex =
        (queue->nextIndex + 1) % vector_size(queue->data);

    queue->count++;
}

Data queue_get(const Queue *queue)
{
    if (queue == nullptr || queue->data == nullptr || queue->count == 0)
    {
        throw std::out_of_range("Queue is empty");
    }

    return vector_get(queue->data, queue->currentIndex);
}

void queue_remove(Queue *queue)
{
    if (queue == nullptr || queue->data == nullptr || queue->count == 0)
    {
        throw std::out_of_range("Queue is empty");
    }

    queue->currentIndex = (queue->currentIndex + 1) % vector_size(queue->data);

    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    if (queue == nullptr)
    {
        return true;
    }

    return queue->count == 0;
}
