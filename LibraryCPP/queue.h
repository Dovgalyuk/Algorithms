#ifndef QUEUE_H
#define QUEUE_H

#include "vector.h"
#include <deque>

struct Queue {
    std::deque<Vector> elements;
};

Queue* queue_create();
void queue_delete(Queue* queue);
void queue_insert(Queue* queue, const Vector& data);
Vector queue_get(const Queue* queue);
void queue_remove(Queue* queue);
bool queue_empty(const Queue* queue);

#endif