#ifndef QUEUE_H
#define QUEUE_H

#include "stack.h"

template <typename Data>
class Queue {
public:
    // Create empty queue
    Queue() {
        stackData = new Stack<Data>();
        reverted = false;
    }

    // Deletes queue
    ~Queue() = default;

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data) {
        if (reverted) revert();
        stackData->push(data);
    }

    // Retrieves first element from the queue
    Data get() {
        if (!reverted) revert();
        return stackData->get();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove() {
        if (!reverted) revert();
        stackData->pop();
    }

    // Returns true if the queue is empty
    bool empty() {
        return stackData->size() == 0;
    }

    void revert() {
        auto tmpData = new Stack<Data>();
        const int size = stackData->size();
        for (int i = 0; i < size; i++) {
            tmpData->push(stackData->get());
            stackData->pop();
        }

        reverted = !reverted;
        delete stackData;
        stackData = tmpData;
    }

private:
    bool reverted;
    Stack<Data> *stackData;
};

#endif
