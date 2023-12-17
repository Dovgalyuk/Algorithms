#ifndef QUEUE_H
#define QUEUE_H

#include "vector.h"

struct Queue;

Queue *queue_create();
void queue_delete(Queue *queue);
void queue_insert(Queue *queue, const Vector &position);
Vector queue_get(const Queue *queue);
void queue_remove(Queue *queue);
bool queue_empty(const Queue *queue);

#endif 
