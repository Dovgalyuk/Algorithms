#ifndef QUEUE_H
#define QUEUE_H

// Queue of integers

struct Queue;

// Create empty queue
Queue *queue_create();

// Deletes queue
void queue_delete(Queue *queue);

// Includes new element into the queue
void queue_insert(Queue *queue, int data);

// Retrieves first element from the queue
int queue_get(Queue *queue);

// Removes first element from the queue
void queue_remove(Queue *queue);

// Returns true if the queue is empty
bool queue_empty(Queue *queue);

#endif
