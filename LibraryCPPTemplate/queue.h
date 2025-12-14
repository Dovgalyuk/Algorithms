#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "vector.h"

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue() : head_(0), size_(0) {}
    
    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        if (size_ == buffer_.size())
        {
            size_t newSize = buffer_.size() == 0 ? 1 : buffer_.size() * 2;
            Vector<Data> newBuffer;
            newBuffer.resize(newSize);

            for (size_t i = 0; i < size_; ++i)
                newBuffer.set(i, buffer_.get((head_ + i) % buffer_.size()));

            buffer_ = newBuffer;
            head_ = 0;
        }
        buffer_.set((head_ + size_) % buffer_.size(), data);
        ++size_;
    }

    // Retrieves first element from the queue
    Data get() const
    {
        return buffer_.get(head_);
    }

    // Removes first element from the queue
    // Should be O(1) on average
    void remove()
    {
        ++head_;
        --size_;
        if (head_ == buffer_.size())
            head_ = 0;
    }

    // Returns true if the queue is empty
    bool empty() const { return size_ == 0; }

private:
    Vector<Data> buffer_;
    size_t head_;
    size_t size_;
};

#endif
