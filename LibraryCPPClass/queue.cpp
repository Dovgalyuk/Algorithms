#include "queue.h"

#include <stdexcept>

Queue::Queue()
    : head_(0), count_(0)
{
}

Queue::Queue(const Queue &a)
    : buffer_(a.buffer_), head_(a.head_), count_(a.count_)
{
}

Queue &Queue::operator=(const Queue &a)
{
    if (this != &a)
    {
        buffer_ = a.buffer_;
        head_ = a.head_;
        count_ = a.count_;
    }
    return *this;
}

Queue::~Queue()
{
}

void Queue::insert(Data data)
{
    if (count_ == buffer_.size())
        grow();

    // ячейка сразу за последним элементом, с переходом через конец буфера
    const size_t tail = (head_ + count_) % buffer_.size();
    buffer_.set(tail, data);
    ++count_;
}

Data Queue::get() const
{
    if (empty())
        throw std::out_of_range("Queue::get: queue is empty");
    return buffer_.get(head_);
}

void Queue::remove()
{
    if (empty())
        throw std::out_of_range("Queue::remove: queue is empty");
    head_ = (head_ + 1) % buffer_.size();
    --count_;
}

bool Queue::empty() const
{
    return count_ == 0;
}

void Queue::grow()
{
    const size_t old_size = buffer_.size();
    buffer_.resize(old_size == 0 ? 1 : old_size * 2);

    // Буфер был заполнен целиком: элементы шли от head_ до конца,
    // а потом с начала буфера до head_ - 1. Эту вторую часть
    // переносим в новую свободную половину, сразу за старым концом
    for (size_t i = 0; i < head_; ++i)
        buffer_.set(old_size + i, buffer_.get(i));
}