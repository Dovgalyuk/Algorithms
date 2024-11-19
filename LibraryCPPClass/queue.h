#ifndef QUEUE_H
#define QUEUE_H

#include "vector.h"
#include <cstddef>


typedef int Data;

class Queue
{
  public:
    // Create empty queue
    Queue();

    // copy constructor
    Queue(const Queue &a) = delete;

    // assignment operator
    Queue &operator=(const Queue &a) = delete;

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
    // private data should be here
    Vector* m_data;
    size_t offset = 0;
};

#endif
