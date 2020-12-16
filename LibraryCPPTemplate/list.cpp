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
	ListItem* current = head->_next;

	if (head == nullptr) return;
	
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

void MyList::list_insert_after(ListItem* item, Coord value)
{
	ListItem* toInsert = new ListItem(value);
	if (item->_next) toInsert->_next = item->_next;
	item->_next = toInsert;

	_length++;
}

void MyList::push_front(Coord value)
{
	ListItem* item = new ListItem(value);

	item->_next = head;
	head = item;

	_length++;
}

void MyList::list_erase_next(ListItem* item)
{
	ListItem* toDelete = item->_next;
	item->_next = toDelete->_next;
	delete toDelete;
	toDelete = nullptr;

	_length--;
}

void MyList::pop()
{
	ListItem* toDelete = head;
	head = head->_next;
	delete toDelete;
	toDelete = nullptr;

	_length--;
}

size_t MyList::get_length() const
{
	return _length;
}