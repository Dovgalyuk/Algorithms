#include "../LibraryCPP/queue.h"
#include "vector.h"

struct Queue
{
    Vector* vector;
    size_t front;
    size_t rear;
    size_t size;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->vector = vector_create();
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue->size == vector_size(queue->vector)) {
        size_t new_size = vector_size(queue->vector) * 2 + 1;
        Vector* new_vector = vector_create();
        vector_resize(new_vector, new_size);
        
        for (size_t i = 0; i < queue->size; i++) {
            vector_set(new_vector, i, vector_get(queue->vector, (queue->front + i) % vector_size(queue->vector)));
        }

        vector_delete(queue->vector);
        queue->vector = new_vector;
        queue->front = 0;
        queue->rear = queue->size;
    }
    vector_set(queue->vector, queue->rear, data);
    queue->rear = (queue->rear + 1) % vector_size(queue->vector);
    queue->size++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue *queue)
{
    queue->front = (queue->front + 1) % vector_size(queue->vector);
    queue->size - 1;
}

bool queue_empty(const Queue *queue)
{
    if (queue->size == 0) return true;
    else return false;
}
