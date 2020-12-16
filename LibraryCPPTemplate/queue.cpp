#include <stdlib.h>
#include "queue.h"

void Queue::try_update_front()
{
    if (_list->get_length() == 1)
    {
        _front = _rear;
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
    _rear = _list->list_first();

    try_update_front();
}

Coord Queue::get() const
{
    return _front->list_item_data();
}

void Queue::remove()
{
    auto* next_item = _rear;
	while (_list->get_length() != 1 && next_item->list_item_next() != _front)
	{
        next_item = next_item->list_item_next();
	}

    delete _front;
    _front = nullptr;
	
    _front = next_item;
    _front->_next = nullptr;
    _list->_length--;
}

bool Queue::is_empty() const
{
    return (_list->get_length() == 0);
}

