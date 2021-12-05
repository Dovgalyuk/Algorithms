#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue(): _queue(new List<Data>())
    {
    }

    // Deletes queue
    ~Queue()
    {
    }

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        _queue->insert_end(data);
    }

    // Retrieves first element from the queue
    Data get() const
    {
        return _queue->first()->data();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        _queue->erase(_queue->first());
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        if (_queue->Size() == 0)
            return true;
        else
            return false;
    }

private:
    // private data should be here
    List<Data>* _queue;
};

#endif
