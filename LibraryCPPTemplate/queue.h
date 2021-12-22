#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

template <typename Data>
class Queue : private List<Data>
{
public:
    // Create empty queue
    Queue()
    {
        tail = nullptr;
    }

    // Deletes queue
    ~Queue()
    {
    }

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        if (tail == nullptr) {
            tail = List<Data>::insert(data);
        }
        else {
            tail = this->insert_after(tail, data);
        }
    }

    // Retrieves first element from the queue
    Data get()
    {
        return this->first()->data();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        if (this->first() == tail) {
            tail = nullptr;
        }
        this->erase(this->first());

    }

    // Returns true if the queue is empty
    bool empty()
    {
        return (this->first() == nullptr);
    }

private:
    Item* tail;
};

#endif