#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "vector.h"
#include <stdexcept>

template <typename Data>
class Queue {
public:
    // Create empty queue
    Queue();

    // Copy constructor
    Queue(const Queue& a);

    // Assignment operator
    Queue& operator=(const Queue& a);

    // Deletes queue
    ~Queue();

    // Includes new element into the queue
    void insert(Data value);

    // Retrieves first element from the queue
    Data& get() const;

    // Removes first element from the queue
    void remove();

    // Returns true if the queue is empty
    bool empty() const;

private:
    Vector<Data>* data; // Pointer to the data
    size_t frontIndex;
    size_t queueSize;
};

// Constructor
template <typename Data>
Queue<Data>::Queue() : data(new Vector<Data>()), frontIndex(0), queueSize(0) {}

// Copy constructor
template <typename Data>
Queue<Data>::Queue(const Queue<Data>& other)
    : data(new Vector<Data>(*other.data)),
      frontIndex(other.frontIndex),
      queueSize(other.queueSize) {}

// Assignment operator
template <typename Data>
Queue<Data>& Queue<Data>::operator=(const Queue<Data>& other) {
    if (this != &other) {
        delete data;

        data = new Vector<Data>(*other.data);
        frontIndex = other.frontIndex;
        queueSize = other.queueSize;
    }
    return *this;
}

// Destructor
template <typename Data>
Queue<Data>::~Queue() {
    delete data;
}

// Insert a new element
template <typename Data>
void Queue<Data>::insert(Data value) {
    if (queueSize == data->size()) {
        size_t new_size = (queueSize == 0) ? 1 : queueSize * 2;
        Vector<Data>* newData = new Vector<Data>();
        newData->resize(new_size);

        for (size_t i = 0; i < queueSize; ++i) {
            newData->set(i, data->get((frontIndex + i) % data->size()));
        }

        delete data;
        data = newData;
        frontIndex = 0;
    }
    data->set((frontIndex + queueSize) % data->size(), value);
    queueSize++;
}

// Get the front element
template <typename Data>
Data& Queue<Data>::get() const {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }
    return data->get(frontIndex);
}

// Remove the front element
template <typename Data>
void Queue<Data>::remove() {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }
    frontIndex = (frontIndex + 1) % data->size();
    queueSize--;
}

// Check if the queue is empty
template <typename Data>
bool Queue<Data>::empty() const {
    return queueSize == 0;
}

#endif
