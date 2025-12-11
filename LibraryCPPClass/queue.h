#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>
#include <stdexcept>
#include "vector.h"

// Change it to desired type
typedef int Data;

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
    Vector _vector;
    size_t _count;
    size_t _head;
};

#endif
