#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

struct Queue {
    Vector *vector;
    size_t head; 
    size_t tail; 
    size_t size;
};

Queue *queue_create()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for queue\n");
        exit(EXIT_FAILURE);
    }

    queue->vector = vector_create();
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
    if (queue) {
        vector_delete(queue->vector);
        free(queue);
    }
}

void queue_insert(Queue *queue, Data data)
{
    if (queue->size == vector_size(queue->vector)) {

        size_t new_size = queue->size == 0 ? 1 : queue->size * 2;
        vector_resize(queue->vector, new_size);
    }
    vector_resize(queue->vector, vector_size(queue->vector)+1);
    vector_set(queue->vector, queue->tail, data);
    queue->tail++;
    queue->size++;
}

Data queue_get(const Queue *queue)
{
    if (queue_empty(queue)) {
        fprintf(stderr, "Error: Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
    if (queue_empty(queue)) {
        fprintf(stderr, "Error: Queue is empty\n");
        exit(EXIT_FAILURE);
    }

    queue->head++;
    queue->size--;
}

bool queue_empty(const Queue *queue)
{
    return queue->size == 0;
}
