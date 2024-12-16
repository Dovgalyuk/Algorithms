#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "vector.h"

template <typename Data> class Queue
{
public:
    Queue() {}

    ~Queue() {}

    void insert(const Data& data) {
        size_t size = data_.size();
        data_.resize(size + 1);
        data_.set(size, data);
    }

    Data get() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return data_[0];
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
