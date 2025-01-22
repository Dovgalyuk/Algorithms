#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "vector.h"
#include <stdexcept>

template <typename Data>
class Queue {
public:
    Queue() {}

    // Copy constructor
    Queue(const Queue& other) : data_(other.data_) {}

    // Move constructor
    Queue(Queue&& other) noexcept : data_(std::move(other.data_)) {}

    ~Queue() {}

    void insert(const Data& data) {
        data_.resize(data_.size() + 1); 
        data_.set(data_.size() - 1, data);
    }

    Data get() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return data_.get(0);
    }

    void remove() {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        data_.erase(0);
    }

    bool empty() const {
        return data_.size() == 0;
    }

private:
    Vector<Data> data_;
};

#endif
