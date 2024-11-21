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

void Queue::insert(Data data) {
    if (count_ == data_.size()) {
        size_t new_capacity = data_.size() * 2;
        Vector new_data;
        new_data.resize(new_capacity);

        if (front_ < rear_) {
            for (size_t i = front_; i < rear_; ++i) {
                new_data.set(i - front_, data_.get(i));
            }
        } else {
            size_t first_part_size = data_.size() - front_;
            for (size_t i = 0; i < first_part_size; ++i) {
                new_data.set(i, data_.get(front_ + i));
            }
            for (size_t i = 0; i < rear_; ++i) {
                new_data.set(first_part_size + i, data_.get(i));
            }
        }

        rear_ = count_;
        front_ = 0;
        data_ = new_data;
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