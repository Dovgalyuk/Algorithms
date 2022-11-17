#ifndef QUEUE_H
#define QUEUE_H
#include "list.h"

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue()
    {
        list = new List<Data>();
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
            lastItem = list->first();
        }
        else {
            list->insert(data);
        }
    }

    // Retrieves first element from the queue
    Data get() const
    {
        return lastItem->data();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        auto* prev = lastItem->prev();
        list->erase(lastItem);
        lastItem = prev;
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return list->first() == nullptr;
    }

private:
    // private data should be here
    List<Data>* list;
    typename List<Data>::Item* lastItem;
};

#endif
