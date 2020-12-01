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

void List::list_insert(Data value)
{
	ListItem* item = new ListItem(value);
	head = item;
}

void List::list_insert_after(ListItem* item, Data value)
{
	ListItem* toInsert = new ListItem(value);
	if (item->_next) toInsert->_next = item->_next;
	else head = toInsert;
	item->_next = toInsert;
}

void List::Insert(Data value)
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

void List::Pop()
{
	ListItem* toDelete = head;
	if (head->_next) head = head->_next;
	delete toDelete;
}