#ifndef QUEUE_H
#define QUEUE_H

typedef int Data;

struct Queue;

Queue *queue_create();

void queue_delete(Queue *queue);

void queue_insert(Queue *queue, Data data);

Data queue_get(const Queue *queue);

void queue_remove(Queue *queue);

bool queue_empty(const Queue *queue);

#endif
