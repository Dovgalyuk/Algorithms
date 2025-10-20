#include "stack.h"

Stack::Stack() {}

Stack::Stack(const Stack& a) : _list(a._list) {}

Stack& Stack::operator=(const Stack& a)
{
    if (this != &a)
    {
        _list = a._list;
    }
    return *this;
}

Stack::~Stack() {}

void Stack::push(Data data)
{
    _list.insert(data);
}

Data Stack::get() const
{
    if (empty()) return Data();
    return _list.first()->data();
}

void Stack::pop()
{
    if (!empty()) _list.erase_first();
}

bool Stack::empty() const
{
    return _list.first() == nullptr;
}
