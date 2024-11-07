#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "list.h"

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue() : _list()
    {
    }

    // copy constructor
    Queue(const Queue& a) : _list(a._list)
    {
        // implement or disable this function
    }

    // assignment operator
    Queue& operator=(const Queue& a)
    {
        // implement or disable this function
        if (this != &a) {
            this->~Queue();
            new (this) Queue<Data>(a);
        }
        return *this;
    }

    // Deletes queue
    ~Queue()
    {
        while (!empty()) {
            remove();
        }
    }

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        if (_list.last())
            _list.insert_after(_list.last(), data);
        else
            _list.insert(data);
    }

    // Retrieves first element from the queue
    Data get() const
    {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }

        return _list.first()->data();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }

        _list.erase_first();
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return _list.first() == nullptr;
    }

private:
    // private data should be here
    List<Data> _list;
};

#endif
