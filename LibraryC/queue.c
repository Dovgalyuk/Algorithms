#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "vector.h"

typedef struct Queue {
    Vector* vector; // Container for data
    size_t head;    // Index of pointer to first element
    size_t tail;    // Index of pointer to place to insert next element
    size_t count;   // Element counter
    FFree* freeFunc;
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
    q->tail = 0;
    q->count = 0;
    q->freeFunc = f;

    return q;
}

void queue_delete(Queue *queue)
{
    if (queue == NULL)
        return;

    vector_delete(queue->vector);

    free(queue);
}

void queue_insert(Queue *queue, Data data)
{
    if (queue == NULL){
        return;
    }

    size_t size = vector_size(queue->vector);

    vector_set(queue->vector, queue->tail, data);
    queue->count++;

    if(queue->count == size) {
        size_t new_size = size*2;
        vector_resize(queue->vector, new_size);

        if (queue->tail < queue->head) {
            size_t i = 0;
            for (; i <= queue->tail ; i++) {
                memcpy(vector_get(queue->vector, i), vector_get(queue->vector, size + i), sizeof(Data));
                vector_set(queue->vector, i, NULL);
            }
            queue->tail = (queue->tail + size) % new_size;
        }
        size = new_size;

    }

    queue->tail = (queue->tail + 1) % size;
    
}

Data queue_get(const Queue *queue)
{
    if (queue == NULL || queue->count == 0) {
        return (Data)0;
    }

    Data element = vector_get(queue->vector, queue->head);
    if(element == NULL) {
        return VECTOR_EMPTY;
    }
    return element;
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
