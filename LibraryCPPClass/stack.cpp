#include "stack.h"

Stack::Stack()
{
    list = new List();
}

Stack::Stack(const Stack &a)
{
    list = new List(*a.list);
}

Stack &Stack::operator=(const Stack &a)
{
    if (this != &a)
    {
        *list = *a.list;
    }
    return *this;
}

Stack::~Stack()
{
    delete list;
}

void Stack::push(Data data)
{
    list->insert(data);
}

Data Stack::get() const
{
    return list->first()->data();
}

void Stack::pop()
{
    list->erase_first();
}

bool Stack::empty() const
{
    return list->first() == nullptr;
}
