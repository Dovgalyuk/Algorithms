#include <stdlib.h>
#include "list.h"

struct ListItem
{
	Data item;
	ListItem* next, * prev;
};

struct List
{
	ListItem* start;
};

List *list_create()
{
	List* temp = new List;
	temp->start = NULL;
    return temp;
}

void list_delete(List *list)
{
	ListItem* temp = list->start;
	while (temp != NULL)
	{
		temp = list_item_next(list->start);
		delete list->start;
		list->start = temp;
	}
	delete list;
}

ListItem *list_first(List *list)
{
    return list->start;
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
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
	if (list->start == NULL)
	{
		list->start = new ListItem;
		list->start->prev = list->start->next = NULL;
	}
	else
	{
		ListItem* temp = list->start;
		list->start = temp->prev = new ListItem;
		list->start->prev = NULL;
		list->start->next = temp;
	}
	list->start->item = data;
	return list->start;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
	ListItem* temp = item->next;
	item->next = new ListItem;
	item->next->item = data;
	if (temp != NULL)
		temp->prev = item->next;
	item->next->next = temp;
	item->next->prev = item;
    return item->next;
}

ListItem *list_erase(List *list, ListItem *item)
{
	ListItem* temp_next = item->next;
	ListItem* temp_prev = item->prev;
	if (item == list->start)
	{
		list->start = temp_next;
	}
	delete item;
	if (temp_next != NULL)
	{
		temp_next->prev = temp_prev;
	}
	if (temp_prev != NULL)
	{
		temp_prev->next = temp_next;
	}
    return temp_next;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
	return list_erase(list, item->next);
}
