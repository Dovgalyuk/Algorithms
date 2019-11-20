#include <stdlib.h>
#include "list.h"

struct ListItem
{
	Data value;
	ListItem* next;
	ListItem* prev;
};

struct List
{
	ListItem* first;
};

List* list_create()
{
	List* newList = new List();
	return newList;
}

void list_delete(List* list)
{
	ListItem* curr = list->first;
	while (curr != NULL)
	{
		ListItem* next = curr->next;
		delete curr;
		curr = next;
	}
	delete list;
}

ListItem* list_first(List* list)
{
	return list->first;
}

Data list_item_data(const ListItem* item)
{
	return item->value;
}

ListItem* list_item_next(ListItem* item)
{
	return item->next;
}

ListItem* list_item_prev(ListItem* item)
{
	return item->prev;
}

ListItem* list_insert(List* list, Data data)
{
	ListItem* newItem = new ListItem();
	newItem->value = data;

	ListItem* currFirst = list->first;
	if (currFirst == NULL) {
		list->first = newItem;
	}
	else {
		newItem->next = currFirst;
		currFirst->prev = newItem;
		list->first = newItem;
	}
	return newItem;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
	ListItem* newItem = new ListItem();
	newItem->value = data;
	newItem->prev = item;
	newItem->next = item->next;

	if (item->next != NULL)
	{
		item->next->prev = newItem;
	}
	item->next = newItem;

	return newItem;
}

ListItem* list_erase(List* list, ListItem* item)
{
	if (item->prev != NULL) {
		item->prev->next = item->next;
	}
	if (item->next != NULL) {
		item->next->prev = item->prev;
	}
	ListItem* next = item->next;
	if (item = list->first) {
		list->first = next;
	}
	delete item;
	return next;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
	return list_erase(list, item->next);
}
