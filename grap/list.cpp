#include <stdlib.h>
#include "list.h"

struct ListItem
{
	ListItem* pNext;
	Data *data;
};

List<ListItem>::Iterator::Iterator(ListItem *pHead)
{
	this->pHead = pHead;
}


List<ListItem>::Iterator List<ListItem>::Iterator::operator++(int)
{
	Iterator iter = *this;
	pHead = pHead->pNext;
	return iter;
}

ListItem* List<ListItem>::Iterator::operator&() {
	return pHead;
}

Data* List<ListItem>::Iterator::operator*() {
	return pHead->data;
}

bool List<ListItem>::Iterator::operator==(const Iterator iter) {
	return pHead == iter.pHead;
}

bool List<ListItem>::Iterator::operator!=(const Iterator iter) {
	return !(*this == iter.pHead);
}
List<ListItem> *list_create()
{
	List<ListItem>*list = new List<ListItem>;
	list->pHead = NULL;
	return list;
}

void list_delete(List<ListItem> *list)
{
	ListItem* currect = list->pHead;
	while (currect != NULL)
	{
		ListItem* temp = currect->pNext;
		delete currect;
		currect = temp;
	}
	delete list;
}

ListItem *list_first(List<ListItem> *list)
{
	return list->pHead;
}

Data *list_item_data(const ListItem *item)
{
	return item->data;
}

ListItem *list_item_next(ListItem *item)
{
	return item->pNext;
}

ListItem *list_item_prev(ListItem *item)
{
	// Not for single list
	return NULL;
}

ListItem *list_insert(List<ListItem> *list, Data *data)
{
	ListItem* item = new ListItem;
	item->data = data;
	item->pNext = list->pHead;
	list->pHead = item;
	return item;
}

ListItem *list_insert_after(List<ListItem> *list, ListItem *item, Data *data)
{
	ListItem* newItem = new ListItem;
	newItem->data = data;
	newItem->pNext = item->pNext;
	item->pNext = newItem;
	return newItem;
}

ListItem *list_erase(List<ListItem> *list, ListItem *item)
{
	ListItem* currect = list->pHead;
	ListItem* last = (ListItem*)malloc(sizeof(ListItem));
	while (currect != item)
	{
		last = currect;
		currect = currect->pNext;
	}
	if (currect == list->pHead) {
		list->pHead = currect->pNext;
	}
	else {
		last->pNext = currect->pNext;
	}
	delete currect;
	return NULL;
}

ListItem *list_erase_next(List<ListItem> *list, ListItem *item)
{
	ListItem* newItem = item->pNext;
	item->pNext = newItem->pNext;
	delete newItem;
	return item;
}
