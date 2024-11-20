#include "queue.h"
#include <stdexcept>

Queue::Queue() : front_(0), rear_(0), count_(0)
{
    data_.resize(1);
}

Queue::Queue(const Queue &a) : data_(a.data_), front_(a.front_), rear_(a.rear_), count_(a.count_)
{
    // implement or disable this function
}

Queue &Queue::operator=(const Queue &a)
{
    // implement or disable this function
    if(this != &a) {
        data_ = a.data_;
        front_ = a.front_;
        rear_ = a.rear_;
        count_ = a.count_;
    }
    return *this;
}

Queue::~Queue()
{
}

void Queue::insert(Data data)
{
    if (count_ == data_.size()) {
        size_t new_capacity = data_.size() * 2;
        Vector new_data;
        new_data.resize(new_capacity);

        for (size_t i = 0; i < count_; ++i) {
            new_data.set(i, data_.get((front_ + i) % data_.size()));
        }
        data_ = new_data;
        front_ = 0;
        rear_ = count_;
    }

    data_.set(rear_, data);
    rear_ = (rear_ + 1) % data_.size();
    ++count_;
}

Data Queue::get() const
{
    if(empty()) {
        throw std::out_of_range("Queue is empty");
    }
    return data_.get(front_);
}

void Queue::remove()
{
    if(empty()) {
        throw std::out_of_range("Queue is empty");
    }
    front_ = (front_ + 1) % data_.size();
    --count_;
}

bool Queue::empty() const
{
    return count_ == 0;
}