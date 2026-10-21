#include "queue.h"

Queue::Queue() : data(), head(0), count(0)
{
}

Queue::Queue(const Queue &a) : data(a.data), head(a.head), count(a.count)
{
    // implement or disable this function
}

Queue &Queue::operator=(const Queue &a)
{
    // implement or disable this function
    if (this == &a)
        return *this;
    data = a.data;
    head = a.head;
    count = a.count;
    return *this;
}

Queue::~Queue()
{
}

void Queue::insert(Data value)
{
    if (count == data.size()) {
        size_t old_size = data.size();
        size_t new_size = (old_size > 0) ? old_size * 2 : 1;

        if (head != 0 && old_size > 0 && count > 0) {
            Vector tmp;
            tmp.resize(count);
            for (size_t i = 0; i < count; ++i) {
                size_t src = (head + i) % old_size;
                tmp.set(i, data.get(src));
            }
            data.resize(new_size);
            for (size_t i = 0; i < count; ++i) {
                data.set(i, tmp.get(i));
            }
            head = 0;
        }
        else {
            data.resize(new_size);
        }
    }

    size_t tail = (head + count) % data.size();
    data.set(tail, value);
    ++count;
}

Data Queue::get() const
{
    if (count == 0)
        throw std::underflow_error("Queue::get: queue is empty");
    return data.get(head);
}

void Queue::remove()
{
    if (count == 0) throw std::underflow_error("Queue::remove: queue is empty");
    head = head + 1;
    count--;
    if (head == data.size()) {
        head = 0;
    }
}

bool Queue::empty() const
{
    return count == 0;
}
