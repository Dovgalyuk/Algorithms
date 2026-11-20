#include "queue.h"
#include <stdexcept>

Queue::Queue()
{
    data.resize(4);
    head = 0;
    count = 0;
}

Queue::Queue(const Queue& a)
{
    data = a.data;
    head = a.head;
    count = a.count;
}

Queue& Queue::operator=(const Queue& a)
{
    if (this == &a)
    {
        return *this;
    }

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
    if (count == data.size())
    {
        size_t old_capacity = data.size();
        size_t new_capacity = old_capacity * 2;

        Vector new_data;
        new_data.resize(new_capacity);

        for (size_t i = 0; i < count; i++)
        {
            new_data.set(i, data.get((head + i) % old_capacity));
        }

        data = new_data;
        head = 0;
    }

    size_t index = (head + count) % data.size();

    data.set(index, value);
    count++;
}

Data Queue::get() const
{
    if (empty())
    {
        throw std::underflow_error("Queue is empty");
    }

    return data.get(head);
}

void Queue::remove()
{
    if (empty())
    {
        throw std::underflow_error("Queue is empty");
    }

    head = (head + 1) % data.size();
    count--;
}

bool Queue::empty() const
{
    return count == 0;
}
