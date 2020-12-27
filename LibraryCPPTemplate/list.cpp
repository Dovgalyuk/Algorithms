#include "list.h"

ListItem::ListItem(Coord value, ListItem* next = nullptr)
{
	_value = value;
	_next = next;
}

Coord ListItem::list_item_data() const
{
	return _value;
}

ListItem* ListItem::list_item_next() const
{
	return _next;
}

MyList::MyList()
{
	head = nullptr;
	_length = 0;
}

MyList::~MyList()
{
	ListItem* prev = head;
	if (prev == nullptr) return;

	ListItem* current = head->_next;

	do
	{
		delete prev;
		prev = current;
		current = current->_next;
	} while (current != nullptr);

	head = nullptr;
}

ListItem* MyList::list_first() const
{
	return head;
}

ListItem* MyList::list_insert_after(ListItem* item, Coord value)
{
	ListItem* toInsert = new ListItem(value);
	toInsert->_next = item->_next;
	item->_next = toInsert;

	_length++;
	return toInsert;
}

ListItem* MyList::push_front(Coord value)
{
	ListItem* item = new ListItem(value);

	item->_next = head;
	head = item;

	_length++;
	return item;
}

void MyList::list_erase_next(ListItem* item)
{
	ListItem* toDelete = item->_next;
	item->_next = toDelete->_next;
	delete toDelete;
	//toDelete = nullptr;

	_length--;
}

void MyList::pop()
{
	ListItem* toDelete = head;
	head = head->_next;
	delete toDelete;
	//toDelete = nullptr;

	_length--;
}

size_t MyList::get_length() const
{
	return _length;
}