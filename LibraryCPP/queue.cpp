﻿#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* vector;
    ptrdiff_t head;
    ptrdiff_t rear;

    Queue()
    {
        vector = vector_create();
        vector_resize(vector, 2);
        head = -1;
        rear = -1;
    }
    ~Queue()
    {
        vector_delete(vector);
    }
};

Queue* queue_create()
{
    return new Queue;
}

void queue_delete(Queue* queue)
{
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    size_t size = vector_size(queue->vector);

    if (queue_empty(queue))
    {
        queue->rear = 0;
        queue->head = 0;
    }
    else if (queue->rear % static_cast<int>(size) == queue->head)
    {
        Vector* buff = vector_create();
        vector_resize(buff, size * 2);

        int counter = 0;

        for (size_t i = queue->head; i < size; i++)
        {
            vector_set(buff, counter, vector_get(queue->vector, i));
            counter++;
        }

        for (int i = 0; i < queue->rear; i++)
        {
            vector_set(buff, counter, vector_get(queue->vector, i));
            counter++;
        }

        vector_delete(queue->vector);
        queue->vector = buff;

        queue->head = 0;
        queue->rear = static_cast<int>(size);

        size = vector_size(queue->vector);
    }

    auto rear = queue->rear % size;
    vector_set(queue->vector, rear, data);
    queue->rear = rear + 1;
}

Data queue_get(const Queue* queue)
{
    if (!queue_empty(queue))
    {
        Data value = vector_get(queue->vector, queue->head);
        return value;
    }
    return Data();
}

void queue_remove(Queue* queue)
{
    size_t size = vector_size(queue->vector);
    auto head = queue->head;

    if (!queue_empty(queue))
    {
        head++;

        if (queue->rear == head)
        {
            queue->head = -1;
            queue->rear = -1;
        }
        else
            queue->head = head % size;
    }
}

bool queue_empty(const Queue* queue)
{
    return (queue->rear == -1 && queue->head == -1);
}