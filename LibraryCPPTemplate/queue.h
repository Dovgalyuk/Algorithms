#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

template <typename Data>
class Queue : private List<Data>{
public:
    // Create empty queue
    Queue() : List<Data>() {
        last = nullptr;
    }

    // Deletes queue
    ~Queue() = default;

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data) {
        auto *item = List<Data>::insert(data);
        if (last == nullptr)
            last = item;
    }

    // Retrieves first element from the queue
    Data get() {
        return last->data();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove() {
        auto *item = last;
        last = item->prev();
        this->erase(item);
    }

    // Returns true if the queue is empty
    bool empty() const {
        return this->getSize() == 0;
    }

private:
    typename List<Data>::Item *last;
};

#endif
