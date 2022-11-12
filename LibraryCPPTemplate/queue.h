#ifndef QUEUE_H
#define QUEUE_H
#include <list.h>

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue()
    {
        _list = new List<Data>();
    }

    // Deletes queue
    ~Queue()
    {
        delete _list;
    }

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        if (empty()) {
            _list->insert(data);
            _last = _list->first();
        } else {
            _list->insert(data);
        }
    }

    // Retrieves first element from the queue
    Data get() const
    {
        return _last->data();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        auto *prev = _last->prev();
        _list->erase(_last);
        _last = prev;
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return _list->first() == nullptr;
    }

private:
    // private data should be here
    List<Data>* _list;
    typename List<Data>::Item* _last;
};

#endif
