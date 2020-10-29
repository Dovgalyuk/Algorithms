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

	if (head == nullptr)
		head = item;
	else
	{
		/*ListItem* current = head;

		while (current->_next != nullptr)
			current = current->_next;

		current->_next = item;
		head = item;*/
		item->_next = head;
		head = item;
	}
}

void List::list_erase_next(ListItem* item)
{
	ListItem* toDelete = item->_next;
	if (toDelete) // function named list_erase_NEXT so i decided if there's no next element don't delete anyhing
	{
		if (toDelete->_next) item->_next = toDelete->_next;
		else item->_next = nullptr;
		delete toDelete;
	}
	else // if no next element deleting current
	{
		ListItem* prev = this->head;
		while (prev->_next != item) //finding prev
			prev = prev->_next;
		if (item->_next) prev->_next = item->_next;
		else prev->_next = nullptr;
		delete item;
	}
}

void List::Pop()
{
	ListItem* toDelete = head;
	if (head->_next) head = head->_next;
	delete toDelete;
}