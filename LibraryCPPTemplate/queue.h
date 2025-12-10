#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "vector.h"

template <typename Data> class Queue
{
public:
    // Create empty queue
    Queue()
    {
        buffer_.resize(4);
        head_ = 0;
        tail_ = 0;
        count_ = 0;
    }

    // copy constructor
    Queue(const Queue &a)
    {
        buffer_ = a.buffer_;
        head_ = a.head_;
        tail_ = a.tail_;
        count_ = a.count_;
    }

    // assignment operator
    Queue &operator=(const Queue &a)
    {
        if (this == &a)
            return *this;

        buffer_ = a.buffer_;
        head_ = a.head_;
        tail_ = a.tail_;
        count_ = a.count_;
        return *this;
    }

    // Deletes queue
    ~Queue()
    {
    }

    // Includes new element into the queue
    // Should be O(1) on average
    void insert(Data data)
    {
        if (count_ == buffer_.size())
            expand();

        buffer_.set(tail_, data);
        tail_ = (tail_ + 1) % buffer_.size();
        ++count_;
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
        head_ = (head_ + 1) % buffer_.size();
        --count_;
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return count_ == 0;
    }

private:
    Vector<Data> buffer_;
    size_t head_;
    size_t tail_;
    size_t count_;

    void expand()
    {
        size_t oldSize = buffer_.size();
        Vector<Data> newBuffer;
        newBuffer.resize(oldSize * 2);

        for (size_t i = 0; i < count_; ++i)
            newBuffer.set(i, buffer_.get((head_ + i) % oldSize));

        buffer_ = newBuffer;
        head_ = 0;
        tail_ = count_;
    }
};

#endif
