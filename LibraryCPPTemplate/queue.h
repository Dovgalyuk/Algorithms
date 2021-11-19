#ifndef QUEUE_H
#define QUEUE_H
#include "list.h"

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue()
    {
    }

    // Deletes queue
    ~Queue()
    {
        delete list;
    }

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        if (empty()) {
            list->insert(data);
        } else {
            list->insert_after(list->first()->prevItem, data);
        }
    }

    // Retrieves first element from the queue
    Data get() const
    {
        return list->first()->data();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        list->erase(list->first());
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return !list->first();
    }

private:
    List<Data>* list = new List<Data>;
};

#endif
