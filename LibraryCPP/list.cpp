#include "list.h"

ListItem::ListItem(Data value, ListItem* next = nullptr)
{
	_value = value;
	_next = next;
}

Data ListItem::list_item_data() const
{
	return _value;
}

ListItem* ListItem::list_item_next() const
{
	return _next;
}

List::List()
{
	head = nullptr;
}

List::~List()
{
	ListItem* prev = head;
	ListItem* current = head->_next;
	do
	{
		delete prev;
		prev = current;
		current = current->_next;
	} while (current != nullptr);

	head = nullptr;
}

ListItem* List::list_first() const
{
	return head;
}

void List::list_insert_after(ListItem* item, Data value)
{
	ListItem* toInsert = new ListItem(value);
	if (item->_next) toInsert->_next = item->_next;
	item->_next = toInsert;
}

void List::push_front(Data value)
{
	ListItem* item = new ListItem(value);

	item->_next = head;
	head = item;
}

void List::list_erase_next(ListItem* item)
{
	ListItem* toDelete = item->_next;
	item->_next = toDelete->_next;
	delete toDelete;
	toDelete = nullptr;
}

void List::pop()
{
	ListItem* toDelete = head;
	head = head->_next; // head can be null so why not
	delete toDelete;
	toDelete = nullptr;
}