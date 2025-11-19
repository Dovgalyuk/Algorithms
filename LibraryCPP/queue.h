#ifndef QUEUE_H
#define QUEUE_H

#include "vector.h"

typedef int Data;

struct Queue
{
    Vector* vector;
    size_t front;
    size_t back;
    size_t count;
};

Queue* queue_create();
void queue_delete(Queue* queue);
void queue_insert(Queue* queue, Data data);
Data queue_get(const Queue* queue);
void queue_remove(Queue* queue);
bool queue_empty(const Queue* queue);

#endif