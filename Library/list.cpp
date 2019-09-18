#include <stdlib.h>
#include "list.h"

struct ListItem
{
	sData item;
	ListItem* next = NULL;
	ListItem* previous = NULL;
};

struct List
{
	ListItem* head = NULL;
};

List *list_create()
{
	List* temp = new List;
	temp->head = NULL;
	return temp;
}

void list_delete(List *list)
{
	ListItem* temp = (list)->head;
	ListItem* next = NULL;

	while (temp)
	{
		next = temp->next;
		delete temp;
		temp = next;
	}
	delete list;
}

ListItem *list_first(List *list)
{
	return list->head;
}

sData list_item_data(const ListItem *item)
{
	return item->item;
}

ListItem *list_item_next(ListItem *item)
{
	return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
	return item->previous;
}

ListItem *list_insert(List *list, sData data)
{
	ListItem* temp = new ListItem;
	temp->item = data;
	temp->next = list->head;
	temp->previous = NULL;
	list->head = temp;
	return temp;
}

ListItem *list_insert_after(List *list, ListItem *item, sData data)
{
	ListItem* temp = new ListItem;

	if (item == NULL) return NULL;
	temp->item = data;
	temp->previous = item;
	temp->next = item->next;
	if (item->next) item->next->previous = temp;
	item->next = temp;
	return NULL;
}

ListItem* list_erase(List* list, ListItem* item)
{
	if (item->next && item->previous)
	{
		item->previous->next = item->next;
		item->next->previous = item->previous;
	}
	if (item->next && !item->previous)
	{
		list->head = item->next;
		item->next->previous = item->previous;
	}
	if (!item->next && item->previous) item->previous->next = item->next;
	delete item;
	return item;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
	return list_erase(list, item->next);
}