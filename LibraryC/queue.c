#include <stdlib.h>
#include "queue.h"
#include "vector.h"

typedef struct Queue {
    Vector* items;
    size_t front;
    size_t rear;
} Queue;


Queue* queue_create(FFree f) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) {
        return NULL;
    }
    else {
        queue->items = vector_create(f);
        queue->front = 0;
        queue->rear = 0;
        return queue;
    }
    
}

void queue_delete(Queue* queue) {
    vector_delete(queue->items);
    free(queue);
}

void queue_insert(Queue* queue, void* data) {
    vector_set(queue->items, queue->rear++, data);
}

void* queue_get(const Queue* queue) {
    if (!queue_empty(queue)) {
        return vector_get(queue->items, queue->front);
    }
    return NULL;
}

void queue_remove(Queue* queue) {
    if (!queue_empty(queue)) {
        queue->front++;
    }
}

bool queue_empty(const Queue* queue) {
    return queue->front == queue->rear;
}