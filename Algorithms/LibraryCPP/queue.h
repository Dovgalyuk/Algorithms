#ifndef QUEUE_H
#define QUEUE_H

// Queue
// Stores integer values inside
typedef int Data;

struct Queue;

// Create empty queue
Queue *queue_create();

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

#endif
