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
        Vector* temp = vector_create(); 
        vector_resize(temp, capacity * 2);

        for (size_t i = 0; i < queue->count; ++i) 
        { 
            size_t index = (queue->head + i) % capacity; 
            vector_set(temp, i, vector_get(queue->data, index));
        }
        
        vector_delete(queue->data);
        queue->data = temp;

        queue->head = 0; 
        capacity = capacity * 2;
    }
    size_t tail = (queue->head + queue->count) % capacity;
    vector_set(queue->data, tail, data);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->data, queue->head);
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

struct PriorityQueue
{
    Vector* data;
};

PriorityQueue* pqueue_create()
{
    PriorityQueue* pq = new PriorityQueue;
    pq->data = vector_create();
    vector_resize(pq->data, 0);
    return pq;
}

void pqueue_delete(PriorityQueue* pq)
{
    vector_delete(pq->data);
    delete pq;
}

bool pqueue_empty(const PriorityQueue* pq)
{
    return vector_size(pq->data) == 0;
}

void pqueue_push(PriorityQueue* pq, int v, const int* dist)
{
    size_t n = vector_size(pq->data);
    vector_resize(pq->data, n + 1);

    size_t pos = n;
    for (size_t i = 0; i < n; i++)
    {
        int u = vector_get(pq->data, i);
        if (dist[v] < dist[u])
        {
            pos = i;
            break;
        }
    }

    for (size_t i = n; i > pos; i--)
    {
        int tmp = vector_get(pq->data, i - 1);
        vector_set(pq->data, i, tmp);
    }

    vector_set(pq->data, pos, v);
}

int pqueue_pop(PriorityQueue* pq)
{
    size_t n = vector_size(pq->data);
    int v = vector_get(pq->data, 0);

    for (size_t i = 1; i < n; i++)
    {
        int tmp = vector_get(pq->data, i);
        vector_set(pq->data, i - 1, tmp);
    }

    vector_resize(pq->data, n - 1);
    return v;
}
