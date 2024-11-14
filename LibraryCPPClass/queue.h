#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>

typedef int Data;
#include "vector.h"

class Queue
{
public:
    // Create empty queue
    Queue();

    // copy constructor
    Queue(const Queue &a);

    // assignment operator
    Queue &operator=(const Queue &a);

    // Deletes queue
    ~Queue();

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data);

    // Retrieves first element from the queue
    Data get() const;

    // Removes first element from the queue
    // Should be O(1) on average
    void remove();

    // Returns true if the queue is empty
    bool empty() const;

private:
    Vector vector_;  // внутренний массив, на основе которого построена очередь
    size_t front_;   // индекс начала очереди
    size_t back_;    // индекс конца очереди
    size_t size_;    // текущий размер очереди
};

#endif
