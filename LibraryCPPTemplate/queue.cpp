#include <stdlib.h>
#include "queue.h"

void Queue::try_update_front(ListItem* li)
{
    if (_list->get_length() == 1)
    {
        _front = li;
    }
}

Queue::Queue()
    :_list(new MyList()), _front(nullptr), _rear(nullptr)
{ }

Queue::~Queue()
{
    delete _list;
}

void Queue::insert(Coord value)
{
    _list->push_front(value);
    ListItem* head = _list->list_first();
    _rear = head;

    try_update_front(head);
}

Coord Queue::get() const
{
    return _front->list_item_data();
}

void Queue::remove()
{
    ListItem* next = _front->list_item_next();
    delete _front;
    _front = next;
	
    _list->_length--;
}

bool Queue::is_empty() const
{
    return (_list->get_length() == 0);
}

