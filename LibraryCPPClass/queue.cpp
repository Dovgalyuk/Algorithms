#include "queue.h"

Queue::Queue()
{
    data.resize(2);
}

Queue::Queue(const Queue &a) = default;
Queue &Queue::operator=(const Queue &a) = default;
Queue::~Queue() = default;

void Queue::insert(Data value)
{
    if (count == data.size()) {
        data.resize(count * 2);
        for (size_t i = 0; i < head; ++i)
            data.set(count + i, data.get(i));
    }
    data.set((head + count) % data.size(), value);
    ++count;
}

Data Queue::get() const
{
    return data.get(head);
}

void Queue::remove()
{
    if (!empty()) {
        head = (head + 1) % data.size();
        --count;
    }
}

bool Queue::empty() const
{
    return count == 0;
}

size_t Queue::size() const
{
    return count;
}
