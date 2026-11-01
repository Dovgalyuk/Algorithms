#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "list.h"

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue()
    {
    }

    // copy constructor
    Queue(const Queue &a)
    {
        data_= a.data_;
    }

    // assignment operator
    Queue &operator=(const Queue &a)
    {
        if (this != &a) {
            data_ = a.data_;
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
        data_.insert_after(data_.last(),data);
    }

    // Retrieves first element from the queue
    Data get() const
    {
        return data_.first()->data();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        data_.erase_first();
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return data_.first()== nullptr;
    }

private:
    List<Data> data_;
};

#endif
