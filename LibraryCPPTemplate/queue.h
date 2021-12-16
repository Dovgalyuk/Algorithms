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
        if (this->getSize() != 0) {
            List<Data>::insert(data);
            return;
        }

        last = List<Data>::insert(data);
    }

    // Retrieves first element from the queue
    Data get() {
        return last->data();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove() {
        if (last == nullptr) return;

        auto *prevItem = last->prev();
        this->erase(last);
        last = prevItem;
    }

    // Returns true if the queue is empty
    bool empty() const {
        return this->getSize() == 0;
    }

    int size() {
        return this->getSize();
    }

private:
    typename List<Data>::Item *last;
};

#endif