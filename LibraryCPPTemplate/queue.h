#ifndef QUEUE_H
#define QUEUE_H
#include <list.h>

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue()
    {
        list = new List<Data>();
        size = 0;
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
        if (lastItem) {
            lastItem = list->insert_after(lastItem, data);
        }
        else {
            lastItem = list->insert(data);
        }
        size++;
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
        size--;
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return (size == 0);
    }

private:
    // private data should be here
    List<Data>* list;
    size_t size;
    typename List<Data>::Item *lastItem = nullptr;
};

#endif
