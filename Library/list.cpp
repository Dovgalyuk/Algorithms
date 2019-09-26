#include <stdlib.h>
#include "list.h"

struct ListItem
{
	Data item;
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
	ListItem* temp = list->head;
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

Data list_item_data(const ListItem *item)
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

ListItem *list_insert(List *list, Data data)
{

	ListItem* temp = new ListItem;

	temp->item = data;
	temp->next = list->head;
	if (list->head) 
	{
		list->head->previous = temp;
	}
	list->head = temp;
	return temp;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
	ListItem* temp = new ListItem;

	if (item == NULL)
	{
		return NULL;
	}
	temp->item = data;
	temp->previous = item;
	temp->next = item->next;
	if (item->next) item->next->previous = temp;
	item->next = temp;
	return temp;
}

ListItem* list_erase(List* list, ListItem* item)
{
	if (item->next && item->previous)
	{
		item->previous->next = item->next;
		item->next->previous = item->previous;
	}
	else if (item->next)
	{
		list->head = item->next;
		item->next->previous = item->previous;
	}
	else if (item->previous)
	{
		item->previous->next = item->next;
	}
	else
	{
		list->head = NULL;
	}
	ListItem* next = item->next;
	delete item;
	return next;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
	return list_erase(list, item->next);
}