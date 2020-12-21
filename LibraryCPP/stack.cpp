#include <stdlib.h>
#include "stack.h"
#include "list.h"

Stack::Stack()
{
    _list = new List();
}

Stack::~Stack()
{
    delete _list;
}

void Stack::Push(Data data)
{
    _list->push_front(data);
}

Data Stack::Get()
{
    return _list->list_first()->list_item_data();
}

void Stack::Pop()
{
    _list->pop();
}

bool Stack::Empty()
{
    if (_list->list_first() == nullptr)
        return true;
    return false;
}