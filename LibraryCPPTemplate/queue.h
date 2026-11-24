#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include <stdexcept>

#include "list.h"

template <typename Data>
class Queue
{
public:
    Queue() = default;
    Queue(const Queue &a) = default;
    Queue &operator=(const Queue &a) = default;
    ~Queue() = default;

    // Adds an element to the end
    void insert(Data data)
    {
        values.insert_after(values.last(), data);
    }

    // Returns the first element without removing it
    Data get() const
    {
        if (empty())
        {
            throw std::out_of_range("Queue is empty");
        }

        return values.first()->data();
    }

    // Removes the first element
    void remove()
    {
        if (empty())
        {
            throw std::out_of_range("Queue is empty");
        }

        values.erase_first();
    }

    // Checks whether the queue is empty
    bool empty() const
    {
        return values.first() == nullptr;
    }

private:
    List<Data> values;
};

#endif