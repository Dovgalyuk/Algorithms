#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

// Queue
// Stores pointer to custom user data
typedef void* Data;
// Custom function to free user pointers on delete
typedef void (FFree)(void*);

typedef struct Queue Queue;

#ifdef __cplusplus
extern "C" {
#endif

// Create empty queue
Queue *queue_create(FFree f);

// Deletes queue
void queue_delete(Queue *queue);

// Includes new element into the queue
// Should be O(1) on average
void queue_insert(Queue *queue, Data data);

// Retrieves first element from the queue
Data queue_get(const Queue *queue);

// Removes first element from the queue
// Should be O(1) on average
void queue_remove(Queue *queue);

// Returns true if the queue is empty
bool queue_empty(const Queue *queue);

#ifdef __cplusplus
}
#endif

#endif
