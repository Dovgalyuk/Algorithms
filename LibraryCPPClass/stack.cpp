#include "stack.h"

Stack::Stack() {}

Stack::Stack(const Stack& a) : _list(a._list) {}

Stack& Stack::operator=(const Stack& a)
{
    _list = a._list;
    return *this;
}

Stack::~Stack() {}

void Stack::push(Data data)
{
    _list.insert(data);
}

// Прикол с const позже пересмотреть!
Data Stack::get() const
{
    if (empty()) return Data();
    List temp = _list;
    return temp.first()->data();
}

void Stack::pop()
{
    if (!empty()) _list.erase_first();
}

// Прикол с const позже пересмотреть!
bool Stack::empty() const
{
    List temp = _list;
    return temp.first() == nullptr;
}
