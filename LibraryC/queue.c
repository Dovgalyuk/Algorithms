#include "queue.h"
#include "list.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct Queue {
  List *list;
} Queue;

Queue *queue_create(FFree f) {
  Queue *queue = malloc(sizeof(Queue));
  if (queue == NULL) {
    return NULL;
  }

  queue->list = list_create(f);
  if (queue->list == NULL) {
    free(queue);
    return NULL;
  }

  return queue;
}

void queue_delete(Queue *queue) {
  if (queue == NULL) {
    return;
  }

  list_delete(queue->list);
  free(queue);
}

void queue_insert(Queue *queue, Data data) {
  if (queue == NULL) {
    return;
  }

  list_insert_tail(queue->list, data);
}

Data queue_get(const Queue *queue) {
  if (queue == NULL) {
    return (Data)0;
  }

  ListItem *first = list_first(queue->list);
  return list_item_data(first);
}

void queue_remove(Queue *queue) {
  if (queue == NULL) {
    return;
  }

  list_erase_first(queue->list);
}

bool queue_empty(const Queue *queue) {
  if (queue == NULL) {
    return true;
  }

  return list_first(queue->list) == NULL;
}
