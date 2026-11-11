#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "list.h"

using namespace std;

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue()
    {
    }

    // copy constructor
    Queue(const Queue &a) : list(a.list)
    {
        // implement or disable this function
    }

    // assignment operator
    Queue &operator=(const Queue &a)
    {
        // implement or disable this function
        list = a.list;
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
        list.insert_after(list.last(), data);
    }

    // Retrieves first element from the queue
    Data get() const
    {
        if (list.first())
            return list.first()->data();
        return Data();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        list.erase_first();
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return list.first() == nullptr;
    }

private:
    // private data should be here
    // Методы first() и last() в List не имеют const-версий.
    mutable List<Data> list;
};

#endif
