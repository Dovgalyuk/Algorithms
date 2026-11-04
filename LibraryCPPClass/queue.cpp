#include "queue.h"
Queue::Queue()
    : first(0), count(0)
{
    data.resize(4);
}

Queue::Queue(const Queue &a)
    : data(a.data), first(a.first), count(a.count)
{
}

Queue &Queue::operator=(const Queue &a)
{
    if (this == &a) return *this;
    data = a.data;
    first = a.first;
    count = a.count;
    return *this;
}

Queue::~Queue()
{
}

void Queue::insert(Data data)
{
    if (count == this->data.size()) {
        Vector values;
        values.resize(this->data.size() * 2);
        for (size_t i = 0; i < count; i++) values.set(i, this->data.get((first + i) % this->data.size()));
        this->data = values;
        first = 0;
    }
    this->data.set((first + count) % this->data.size(), data);
    count++;
}

Data Queue::get() const
{
    return count == 0 ? Data() : data.get(first);
}

void Queue::remove()
{
    if (count > 0) {
        first = (first + 1) % this->data.size();
        count--;
    }
}

bool Queue::empty() const
{
    return count == 0;
}
