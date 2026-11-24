#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include <stdexcept>
#include "list.h"

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue()
    {
    }

    // copy constructor
    Queue(const Queue &a) : items_(a.items_)
    {
    }

    // assignment operator
    Queue &operator=(const Queue &a)
    {
        items_ = a.items_;
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
        items_.insert_after(items_.last(), data);
    }

    // Retrieves first element from the queue
    Data get() const
    {
        if (empty())
            throw std::out_of_range("Queue: get from empty queue");
        return items_.first()->data();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        if (empty())
            throw std::out_of_range("Queue: remove from empty queue");
        items_.erase_first();
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return items_.first() == nullptr;
    }

private:
    List<Data> items_;
};

#endif
