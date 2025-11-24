#include "stack.h"

Stack::Stack()
{
    _list = new List();
}

Stack::Stack(const Stack &a)
{
    _list = new List(*a._list);
}

Stack &Stack::operator=(const Stack &a)
{
    if(this != &a)
    {
        delete _list;
        _list = new List(*a._list);
    }
    return *this;
}

Stack::~Stack()
{
     if (_list != nullptr) 
    {
        delete _list;
        _list = nullptr;
    }
}

void Stack::push(Data data)
{
    _list->insert(data);
}

Data Stack::get() const
{
    return _list->first()->data();
}

void Stack::pop()
{
    if(!empty())
    {
        _list->erase_first();
    }
}

bool Stack::empty() const
{
    return _list->first()==nullptr;
}
