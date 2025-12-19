#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "vector.h"

typedef struct Queue {
    Vector* vector; // Container for data
    size_t head;    // Index of pointer to first element
    size_t count;   // Element counter
} Queue;

Queue *queue_create(FFree f)
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        return NULL;
    }

    q->vector = vector_create(f);
    if (q->vector == NULL) {
        free (q);
        return NULL;
    }

    vector_resize(q->vector, (size_t)1);
    q->head = 0;
    q->count = 0;
    return q;
}

void queue_delete(Queue *queue)
{
    if (queue == NULL)
        return;

    vector_delete(queue->vector);

    free(queue);
}

void queue_insert(Queue *queue, Data data) {
    if (queue == NULL) return;

    size_t size = vector_size(queue->vector);

    size_t tail = (queue->head + queue->count) % size;
    
    if (queue->count == size) {
        size_t old_size = size;
        size_t new_size = old_size * 2;
        vector_resize(queue->vector, new_size);

        if (tail <= queue->head) {
            for (size_t i = 0; i < tail; i++) {
                Data d = vector_get(queue->vector, i);
                vector_set(queue->vector, old_size + i, d);                 
            }
            tail = old_size + tail;
        }
        size = new_size;
    }

    vector_set(queue->vector, tail, data);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    if (queue == NULL || queue->count == 0) {
        return (Data)0;
    }

    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
    if (queue == NULL ) {
        return;
    }

    size_t size = vector_size(queue->vector);
    if (size == 0 || queue->count == 0) {
        return;
    }

    vector_set(queue->vector, queue->head, NULL);
    queue->head = (queue->head + 1) % size;
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    if(queue == NULL || queue->count == 0)
        return true;
    else    
        return false;
}
