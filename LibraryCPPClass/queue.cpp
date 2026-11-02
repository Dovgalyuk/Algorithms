#include "queue.h"
Queue::Queue()
    : capacity(4), first(0), count(0)
{
    data.resize(capacity);
}

Queue::Queue(const Queue &a)
    : capacity(a.capacity), first(0), count(a.count)
{
    data.resize(capacity);
    for (size_t i = 0; i < count; i++) data.set(i, a.data.get((a.first + i) % a.capacity));
}

Queue &Queue::operator=(const Queue &a)
{
    if (this == &a) return *this;
    data = a.data;
    capacity = a.capacity;
    count = a.count;
    first = 0;
    return *this;
}

Queue::~Queue()
{
}

void Queue::insert(Data data)
{
    if (count == capacity) {
        Vector values;
        values.resize(capacity * 2);
        for (size_t i = 0; i < count; i++) values.set(i, this->data.get((first + i) % capacity));
        this->data = values;
        capacity *= 2;
        first = 0;
    }
    this->data.set((first + count) % capacity, data);
    count++;
}

Data Queue::get() const
{
    return count == 0 ? Data() : data.get(first);
}

void Queue::remove()
{
    if (count > 0) {
        first = (first + 1) % capacity;
        count--;
    }
}

bool Queue::empty() const
{
    return count == 0;
}
