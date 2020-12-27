#include <stdlib.h>
#include "queue.h"

Queue::Queue()
    :_list(new MyList()), _front(nullptr), _rear(nullptr)
{ }

Queue::~Queue()
{
    delete _list;
}

void Queue::insert(Coord value)
{
	if (_list->get_length() == 0)
	{
        _rear = _list->push_front(value);
        _front = _rear;
	}
    else
    {
        _rear = _list->list_insert_after(_rear, value);
    }
}

Coord Queue::get() const
{
    return _front->list_item_data();
}

void Queue::remove() const
{
    _list->pop();
}

bool Queue::is_empty() const
{
    return (_list->get_length() == 0);
}

