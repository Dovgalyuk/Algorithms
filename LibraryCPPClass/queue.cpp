#include "queue.h"
#include "vector.h"
#include <stdexcept>
#include <utility>

Queue::Queue() : vector_(), head_(0), size_(0)
{
}

Queue::Queue(const Queue& a)
    : vector_(a.vector_), head_(a.head_), size_(a.size_)
{
}

Queue& Queue::operator=(const Queue& a)
{
    if (this == &a)
        return *this;

    Queue temp(a);
    std::swap(vector_, temp.vector_);
    std::swap(head_, temp.head_);
    std::swap(size_, temp.size_);
    return *this;
}

Queue::~Queue()
{
}

void Queue::insert(Data data)
{
    if (size_ == vector_.size()) {
        expandIfNeeded();
    }

    size_t capacity = vector_.size();
    size_t tail = (head_ + size_) % capacity;

    vector_.set(tail, data);
    ++size_;
}

Data Queue::get() const
{
    if (empty())
        throw std::out_of_range("Queue::get: queue is empty");
    return vector_.get(head_);
}

void Queue::remove()
{
    if (empty())
        throw std::out_of_range("Queue::remove: queue is empty");

    size_t capacity = vector_.size();
    head_ = (head_ + 1) % capacity;
    --size_;
}

bool Queue::empty() const
{
    return size_ == 0;
}

void Queue::expandIfNeeded()
{
    size_t old_capacity = vector_.size();
    size_t new_capacity = (old_capacity == 0) ? 1 : old_capacity * 2;

    Vector new_vector;
    new_vector.resize(new_capacity);

    for (size_t i = 0; i < size_; ++i) {
        size_t old_index = (head_ + i) % old_capacity;
        new_vector.set(i, vector_.get(old_index));
    }

    vector_ = new_vector;
    head_ = 0;
}