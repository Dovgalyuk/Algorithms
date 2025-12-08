#include "queue.h"

Queue::Queue() : _size(0), _head(0), _tail(0) {}

Queue::Queue(const Queue &a) : _vector(a._vector), _size(a._size), _head(a._head), _tail(a._tail) {}

Queue &Queue::operator=(const Queue &a)
{
    if (this != &a)
    {
        _vector = a._vector;
        _size = a._size;
        _head = a._head;
        _tail = a._tail;
    }
    return *this;
}

Queue::~Queue()
{
}

void Queue::insert(Data data)
{
    if (_size == _vector.size())
    {
        size_t capacity;
        if(_size == 0) capacity = 4;
        else capacity = _size * 2;

        _vector.resize(capacity);

        _head = 0;
        _tail = _size;
    }

    _vector.set(_tail, data);
    _tail = (_tail + 1) % _vector.size();
    _size++;
}

Data Queue::get() const
{
    if(empty())
    {
        throw std::runtime_error("Queue is empty");
    }
    return _vector.get(_head);
}

void Queue::remove()
{
    if(empty())
    {
        throw std::runtime_error("Queue is empty");
    }

    _head = (_head + 1) % _vector.size();
    _size--;

    if (_size > 0 && _size < _vector.size() / 4)
    {
        _vector.resize(_vector.size() / 2);
        
        _head = 0;
        _tail = _size;
    }

}

bool Queue::empty() const
{
    return _size == 0;
}
