#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>
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
    size_t size() const {return count;}

private:
    // private data should be here
    Vector buffer;   // underlying storage
    size_t head;     // index of front element
    size_t count;    // number of elements

    void grow_if_needed();
    void copy_from(const Queue& a);
    size_t tail() const { return (head + count) % buffer.size(); }
};

#endif
