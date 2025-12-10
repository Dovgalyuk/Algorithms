#include "queue.h"
#include <stdexcept>

Queue::Queue() : buffer(), head(0), count(0)
{
    buffer.resize(4);
}

void Queue::copy_from(const Queue& a)
{
    head = a.head;
    count = a.count;
    buffer = a.buffer;
}
Queue::Queue(const Queue &a) : buffer(), head(0), count(0)
{
    // implement or disable this function
    copy_from(a);
}

Queue &Queue::operator=(const Queue &a)
{
    // implement or disable this function
    if (this == &a) return *this;
    copy_from(a);
    return *this;
}

Queue::~Queue()
{
}

void Queue::insert(Data data)
{
    grow_if_needed();
    // put at tail
    if (buffer.size() == 0) {
        buffer.resize(1);
        head = count = 0;
    }
    buffer.set(tail(), data);
    ++count;
}

Data Queue::get() const
{
    if (empty()) throw std::runtime_error("Queue::get from empty queue");
    return buffer.get(head);
}

void Queue::remove()
{
    if (empty()) throw std::runtime_error("Queue::remove from empty queue");
    head = (head + 1) % buffer.size();
    --count;
    if (count == 0) {
        head = 0;
    }
}

bool Queue::empty() const
{
    return count == 0;
}

void Queue::grow_if_needed()
{
    if (count < buffer.size()) return;
    size_t newcap = (buffer.size() == 0) ? 1 : buffer.size() * 2;
    Vector newbuf;
    newbuf.resize(newcap);

    for (size_t i = 0; i < count; ++i) {
        size_t idx = (head + i) % buffer.size();
        newbuf.set(i, buffer.get(idx));
    }
    buffer = newbuf;
    head = 0;
}