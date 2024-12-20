#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "vector.h"
#include <type_traits>

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue();

    // copy constructor
    Queue(const Queue &a);

    // assignment operator
    Queue &operator=(const Queue &a);

    // Deletes queue
    ~Queue();

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data value);

    // Retrieves first element from the queue
    Data& get() const;

    // Removes first element from the queue
    // Should be O(1) on average
    void remove();

    // Returns true if the queue is empty
    bool empty() const;

private:
    // private data should be here
    Vector<Data> data;
    size_t frontIndex;
    size_t queueSize;
};

// Constructor
template <typename Data>
Queue<Data>::Queue() : data(), frontIndex(0), queueSize(0) {}

// Copy constructor
template <typename Data>
Queue<Data>::Queue(const Queue<Data>& other): data(other.data), frontIndex(other.frontIndex), queueSize(other.queueSize) {}

// Assignment operator
template <typename Data>
Queue<Data>& Queue<Data>::operator=(const Queue<Data>& other) {
    if (this == &other) {
        return *this;
    }

    data = other.data; 
    frontIndex = other.frontIndex;
    queueSize = other.queueSize;

    return *this;
}

template <typename Data>
Queue<Data>::~Queue() {
    // destruct Vector
}

template <typename Data>
void Queue<Data>::insert(Data value) {
    if (queueSize == data.size()) {
        size_t new_size = (queueSize == 0) ? 1 : queueSize * 2;
        data.resize(new_size);

        size_t count = 0; 
        size_t current = frontIndex;
        Data temp = data.get(current);

        while (count < queueSize) {
            size_t next = (current + queueSize - frontIndex) % queueSize;
            Data swapping =  data.get(next);
            data.set(next, temp);
            temp = swapping;
            current = next; 
            ++count;
        }

        frontIndex = 0;
    }
    data.set((frontIndex + queueSize) % data.size(), value);
    queueSize++;
}


template <typename Data>
Data& Queue<Data>::get() const {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }
    return data.get(frontIndex);
}

// Dequeue: Remove element from the front
template <typename Data>
void Queue<Data>::remove() {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }

    
    frontIndex = (frontIndex + 1) % data.size();
    queueSize--;
}

template <typename Data>
bool Queue<Data>::empty() const {
    return queueSize == 0;
}

#endif