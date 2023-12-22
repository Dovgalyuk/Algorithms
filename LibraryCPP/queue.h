#ifndef QUEUE_H
#define QUEUE_H

#include "vector.h"

typedef char Data;

struct Queue;
// Creates a new queue
Queue* queue_create();

// Deletes the queue and frees the memory
void queue_delete(Queue* queue);

// Inserts an element into the queue
void queue_insert(Queue* queue, Data data);

// Gets the front element of the queue
Data queue_get(const Queue* queue);

// Removes the front element from the queue
void queue_remove(Queue* queue);

// Checks if the queue is empty
bool queue_empty(const Queue* queue);

#endif