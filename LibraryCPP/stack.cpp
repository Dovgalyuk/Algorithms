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
<<<<<<< HEAD
    _list->push_front(data);
=======
    _list->Insert(data);
>>>>>>> 547f7fc0a8ca7bf2c2e410c9a04bb5f559cc353c
}

Data Stack::Get()
{
    return _list->list_first()->list_item_data();
}

void Stack::Pop()
{
<<<<<<< HEAD
    _list->pop();
=======
    /*ListItem* li = _list->list_first();
    if (li == nullptr) return;
    while (li->list_item_next()->list_item_next() != nullptr)
    {
        li = li->list_item_next();
    }
    _list->list_erase_next(li);*/
   /* if (Empty()) return;
    ListItem* oldHead = _list->list_first();
    ListItem* newHead = _list->list_first()->list_item_next();
    delete _list->list_first()*/;
    _list->Pop();
>>>>>>> 547f7fc0a8ca7bf2c2e410c9a04bb5f559cc353c
}

bool Stack::Empty()
{
    if (_list->list_first() == nullptr)
        return true;
    return false;
}