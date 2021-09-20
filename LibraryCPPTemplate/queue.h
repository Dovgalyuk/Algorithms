#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

template <typename Data>
class Queue : private List<Data>{
public:
    // Create empty queue
    Queue() : List<Data>() {}

    // Deletes queue
    ~Queue() = default;

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data) {
        this->ins(data);
    }

    // Retrieves first element from the queue
    Data get() {
        return this->last()->data();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove() {
        this->erase(this->last());
    }

    // Returns true if the queue is empty
    bool empty() const {
        return this->getSize() == 0;
    }
};

#endif
