#ifndef QUEUE_H
#define QUEUE_H

#include "stack.h"

template <typename Data>
class Queue {
public:
    // Create empty queue
    Queue() = default;

    // Deletes queue
    ~Queue() = default;

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data) {
        upData.push(data);
    }

    // Retrieves first element from the queue
    Data get() {
        checkDownData();
        return downData.get();
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove() {
        checkDownData();
        downData.pop();
    }

    // Returns true if the queue is empty
    bool empty() {
        return upData.size() == 0 && downData.size() == 0;
    }

    void checkDownData() {
        if (!downData.empty()) return;
        const int size = upData.size();
        for (int i = 0; i < size; i++) {
            downData.push(upData.get());
            upData.pop();
        }
    }

private:
    Stack<Data> upData;
    Stack<Data> downData;
};

#endif