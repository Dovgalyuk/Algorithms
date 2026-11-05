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

void Queue::insert(Data value)
{
    if (count == data.size()) {
        Vector values;
        values.resize(data.size() * 2);
        for (size_t i = 0; i < count; i++) values.set(i, data.get((first + i) % data.size()));
        data = values;
        first = 0;
    }
    data.set((first + count) % data.size(), value);
    count++;
}

Data Queue::get() const
{
    return count == 0 ? Data() : data.get(first);
}

void Queue::remove()
{
    if (count > 0) {
        first = (first + 1) % data.size();
        count--;
    }
}

bool Queue::empty() const
{
    return count == 0;
}
