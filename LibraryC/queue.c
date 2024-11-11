// queue.c
#include "queue.h"
#include "vector.h"
#include <stdlib.h>

typedef struct Queue {
  Vector *vector;
  size_t front;
  size_t back;
} Queue;

Queue *queue_create(FFree *f) {
  Queue *queue = malloc(sizeof(Queue));
  if (!queue)
    return NULL;
  queue->vector = vector_create(f);
  if (!queue->vector) {
    free(queue);
    return NULL;
  }
  queue->front = 0;
  queue->back = 0;
  return queue;
}

void queue_delete(Queue *queue) {
  if (!queue)
    return;
  vector_delete(queue->vector);
  free(queue);
}

void queue_insert(Queue *queue, Data data) {
  vector_resize(queue->vector, queue->back + 1);
  vector_set(queue->vector, queue->back, data);
  queue->back++;
}

Data queue_get(const Queue *queue) {
  if (queue_empty(queue))
    return NULL;
  return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue *queue) {
  if (!queue_empty(queue)) {
    queue->front++;
    if (queue->front == queue->back) {
      queue->front = 0;
      queue->back = 0;
      vector_resize(queue->vector, 0);
    }
  }
}

bool queue_empty(const Queue *queue) { return queue->front == queue->back; }
