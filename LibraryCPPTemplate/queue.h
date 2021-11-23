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
        last = nullptr;
    }

    // Deletes queue
    ~Queue()
    {
    }

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        if (last == nullptr) {
            last = List<Data>::insert(data);
        } else {
            last = List<Data>::insert_after(last, data);
        }
    }

    // Retrieves first element from the queue
    Data get()
    {
        return List<Data>::first()->data();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        if (List<Data>::first() == last) {
            last = nullptr;
        }
        this->erase(List<Data>::first());
        
    }

    // Returns true if the queue is empty
    bool empty()
    {
        return (List<Data>::first() == nullptr);
    }

private:
    typename List<Data>::Item *last;
};

#endif
