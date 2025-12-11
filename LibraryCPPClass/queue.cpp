#include "queue.h"

Queue::Queue() : _vector(), _count(0), _head(0)
{
    _vector.resize(4);
}

Queue::Queue(const Queue &a) : _vector(a._vector), _count(a._count), _head(a._head) {}

Queue &Queue::operator=(const Queue &a)
{
    if (this != &a)
    {
        _vector = a._vector;
        _count = a._count;
        _head = a._head;
    }
    return *this;
}

Queue::~Queue()
{
}

void Queue::insert(Data data)
{
    if (_count == _vector.size())
    {
        size_t new_capacity;
        if(_vector.size() == 0) new_capacity = 4;
        else new_capacity = _vector.size() * 2;

        Vector new_vector;
        new_vector.resize(new_capacity);

        for (size_t i = 0; i < _count; i++)
        {
            new_vector.set(i, _vector.get((_head + i) % _vector.size()));
        }

        _vector = new_vector;
        _head = 0;
    }

    size_t _tail = (_head + _count) % _vector.size();
    _vector.set(_tail, data);
    _count++;
}

Data Queue::get() const
{
    if(empty()) return Data();
    else return _vector.get(_head);
}

void Queue::remove()
{
    if(!empty())
    {
        _head = (_head + 1) % _vector.size();
        _count--;
    }    
}

bool Queue::empty() const
{
    return _count == 0;
}
