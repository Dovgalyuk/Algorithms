#ifndef QUEUE_H
#define QUEUE_H
#include <cstddef>
// Queue

// Stores integer values inside
// Change it to desired type
typedef int Data;
struct Position {
    size_t x, y, z; // тесты пришлось менять все...
};
struct Queue;

// Create empty queue
Queue *queue_create();

// Deletes queue
void queue_delete(Queue *queue);

// Includes new element into the queue
// Should be O(1) on average
void queue_insert(Queue *queue, Position position);

// Retrieves first element from the queue
Position queue_get(const Queue *queue);

// Removes first element from the queue
// Should be O(1) on average
void queue_remove(Queue *queue);

// Returns true if the queue is empty
bool queue_empty(const Queue *queue);

#endif
