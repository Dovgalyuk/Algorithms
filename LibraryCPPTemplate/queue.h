#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "vector.h"
#include <cstddef>
#include <stdexcept>

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue() : first(0), count(0)
    {
        buffer.resize(4);
    }

    // copy constructor
    Queue(const Queue &a)
        : buffer(a.buffer), first(a.first), count(a.count)
    {
    }

    // assignment operator
    Queue &operator=(const Queue &a)
    {
        if (this != &a) {
            buffer = a.buffer;
            first = a.first;
            count = a.count;
        }
        return *this;
    }

    // Deletes queue
    ~Queue()
    {
    }

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        if (count == buffer.size()) {
            // Double the buffer and put all elements in queue order.
            Vector<Data> bigger;
            bigger.resize(buffer.size() * 2);
            for (size_t i = 0; i < count; i++)
                bigger.set(i, buffer.get((first + i) % buffer.size()));

            buffer = bigger;
            first = 0;
        }

        size_t last = (first + count) % buffer.size();
        buffer.set(last, data);
        count++;
    }

    // Retrieves first element from the queue
    Data get() const
    {
        if (empty())
            throw std::out_of_range("Queue is empty");
        return buffer.get(first);
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        if (empty())
            throw std::out_of_range("Queue is empty");

        first = (first + 1) % buffer.size();
        count--;
        if (count == 0)
            first = 0;
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return count == 0;
    }

private:
    Vector<Data> buffer; // Ring buffer built on our Vector, not std::vector
    size_t first;        // Index of the first element
    size_t count;        // Number of elements in the queue
};

#endif
