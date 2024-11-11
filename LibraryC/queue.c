#include "queue.h"
#include <stdlib.h>

typedef struct Queue {
  Vector *vector;
  size_t front;
  size_t rear;
} Queue;

Queue *queue_create(FFree f) {
  Queue *queue = malloc(sizeof(Queue));
  if (!queue)
    return NULL;
  queue->vector = vector_create(f);
  queue->front = 0;
  queue->rear = 0;
  return queue;
}

void queue_delete(Queue *queue) {
  vector_delete(queue->vector);
  free(queue);
}

void queue_insert(Queue *queue, Data data) {
  vector_resize(queue->vector, queue->rear + 1);
  vector_set(queue->vector, queue->rear, data);
  queue->rear++;
}

Data queue_get(const Queue *queue) {
  if (queue_empty(queue))
    return NULL;
  return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue *queue) {
  if (queue_empty(queue))
    return;
  queue->front++;
  if (queue->front == queue->rear) {
    queue->front = 0;
    queue->rear = 0;
    vector_resize(queue->vector, 0);
  }
}

bool queue_empty(const Queue *queue) { return queue->front == queue->rear; }
