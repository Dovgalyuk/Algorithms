#include "queue.h"
#include <limits>
#include <stdexcept>

Queue::Queue() : head_(0), count_(0) {}
Queue::Queue(const Queue &a) = default;
Queue &Queue::operator=(const Queue &a) = default;
Queue::~Queue() = default;

void Queue::insert(Data data)
{
    if (count_ == buffer_.size())
    {
        size_t capacity = buffer_.size();
        if (capacity > std::numeric_limits<size_t>::max() / 2)
            throw std::length_error("Queue is too large");
        size_t newCapacity = capacity == 0 ? 4 : capacity * 2;
        Vector grown;
        grown.resize(newCapacity);
        // Restore FIFO order when expanding a wrapped buffer.
        for (size_t i = 0; i < count_; i++)
            grown.set(i, buffer_.get((head_ + i) % capacity));
        buffer_ = grown;
        head_ = 0;
    }
    buffer_.set((head_ + count_) % buffer_.size(), data);
    count_++;
}

Data Queue::get() const
{
    if (empty()) throw std::out_of_range("Queue is empty");
    return buffer_.get(head_);
}

void Queue::remove()
{
    if (empty()) throw std::out_of_range("Queue is empty");
    head_ = (head_ + 1) % buffer_.size();
    count_--;
}

bool Queue::empty() const { return count_ == 0; }
