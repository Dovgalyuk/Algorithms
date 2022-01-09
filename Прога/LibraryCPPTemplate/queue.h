#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

template<typename Data>
class Queue {
private:
    // private data should be here
    Data *queue;
    int size;
    int capacity;

public:
    // Create empty queue
    Queue() : size(0), capacity(10) {
        queue = new Data[capacity];
    }

    // Deletes queue
    ~Queue() {
        delete queue;
        size = 0;
        capacity = 0;
    }

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data) {
        if (size < capacity) {
            queue[size] = data;
            ++size;
        } else {
            capacity *= 2;
            Data *new_queue = new Data[capacity];
            for(int i = 0; i < size; ++i){
                new_queue[i] = queue[i];
            }
            new_queue[size] = data;
            delete[] queue;
            queue = new_queue;
            ++size;
        }
    }

    // Retrieves first element from the queue
    Data get() const {
        if(size == 0){
            return 0;
        }
        Data data = queue[0];
        return data;
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove() {
        if(size == 0) return;

        Data* new_queue = new Data[size - 1];
        --size;
        for(int i = 0; i < size; ++i){
            new_queue[i] = queue[i+1];
        }
        delete[] queue;
        queue = new_queue;
    }

    // Returns true if the queue is empty
    bool empty() const {
        return size > 0;
    }

};

#endif
