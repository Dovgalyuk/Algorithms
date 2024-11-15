#include "queue.h"
#include "vector.h"
#include <stdlib.h>

typedef struct Queue {
  Vector *vector;
  size_t front;
  size_t back;
  size_t size;
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
  queue->size = 0;
  return queue;
}

void queue_delete(Queue *queue) {
  if (!queue)
    return;
  vector_delete(queue->vector);
  free(queue);
}

void queue_insert(Queue *queue, Data data) {
  if (!queue || !queue->vector)
    return;

  size_t capacity = vector_size(queue->vector);

  if (queue->size == 0) {
    queue->front = 0;
    queue->back = 0;
    vector_resize(queue->vector, 1);
    vector_set(queue->vector, 0, data);
    queue->size = 1;
    return;
  }

  if (queue->size >= capacity) {
    if (queue->front > 0 && queue->back < queue->front) {
      size_t new_front = 0;
      size_t new_back = queue->size - 1;
      for (size_t i = queue->front; i < capacity; ++i) {
        vector_set(queue->vector, new_front++, vector_get(queue->vector, i));
      }
      for (size_t i = 0; i <= queue->back; ++i) {
        vector_set(queue->vector, new_front++, vector_get(queue->vector, i));
      }
      queue->front = 0;
      queue->back = new_back;
    }

    size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
    vector_resize(queue->vector, new_capacity);
  }

  queue->back = (queue->back + 1) % vector_size(queue->vector);
  vector_set(queue->vector, queue->back, data);
  queue->size++;
}

Data queue_get(const Queue *queue) {
  if (queue_empty(queue))
    return NULL;
  return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue *queue) {
  if (!queue || queue_empty(queue))
    return;

  vector_set(queue->vector, queue->front, NULL);
  queue->size--;

  if (queue->size == 0) {
    queue->front = 0;
    queue->back = 0;
    vector_resize(queue->vector, 0);
  } else {
    queue->front = (queue->front + 1) % vector_size(queue->vector);
  }
}

bool queue_empty(const Queue *queue) { return queue->size == 0; }
