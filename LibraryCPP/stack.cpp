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
<<<<<<< Updated upstream
<<<<<<< HEAD
    _list->push_front(data);
=======
<<<<<<< HEAD
    _list->push_front(data);
=======
    _list->Insert(data);
>>>>>>> 547f7fc0a8ca7bf2c2e410c9a04bb5f559cc353c
>>>>>>> 551dd8ce8a693e6283c76868950ec1dea528b5b1
=======
    _list->push_front(data);
>>>>>>> Stashed changes
}

Data Stack::Get()
{
    return _list->list_first()->list_item_data();
}

void Stack::Pop()
{
<<<<<<< Updated upstream
<<<<<<< HEAD
    _list->pop();
=======
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
>>>>>>> 551dd8ce8a693e6283c76868950ec1dea528b5b1
=======
    _list->pop();
>>>>>>> Stashed changes
}

bool Stack::Empty()
{
    if (_list->list_first() == nullptr)
        return true;
    return false;
}