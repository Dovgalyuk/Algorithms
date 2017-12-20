#ifndef QUEUE_H
#define QUEUE_H

struct Queue;

Queue *queue_create();

void queue_delete(Queue *queue);

void queue_insert(Queue *queue, int data);

int queue_get(Queue *queue);

void queue_remove(Queue *queue);

bool queue_empty(Queue *queue);

#endif
