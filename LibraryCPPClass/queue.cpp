#include "queue.h"

Queue::Queue() : _vector(), _head(0), _tail(0), _count(0)
{
    _vector.resize(4);
}

Queue::Queue(const Queue& a) : _vector(a._vector), _head(a._head), _tail(a._tail), _count(a._count) {}

Queue& Queue::operator=(const Queue& a)
{
    if (this != &a)
    {
        _vector = a._vector;
        _head = a._head;
        _tail = a._tail;
        _count = a._count;
    }

    return *this;
}

Queue::~Queue() {}

void Queue::insert(Data data)
{
    if (_count == _vector.size())
    {
        size_t new_capacity = _vector.size() * 2;
        if (new_capacity == 0)
        {
            new_capacity = 1;
        }

        Vector new_vector;
        new_vector.resize(new_capacity);
        for (size_t i = 0; i < _count; i++)
        {
            new_vector.set(i, _vector.get((_head + i) % _vector.size()));
        }

        _vector = new_vector;
        _head = 0;
        _tail = _count;
    }

    _vector.set(_tail, data);
    _tail = (_tail + 1) % _vector.size();
    _count++;
}

Data Queue::get() const
{
    return empty() ? Data() : _vector.get(_head);
}

void Queue::remove()
{
    if (!empty())
    {
        _head = (_head + 1) % _vector.size();
        _count--;
    }
}

bool Queue::empty() const
{
    return _count == 0;
}
