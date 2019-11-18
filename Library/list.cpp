#include <stdlib.h>
#include "list.h"

struct ListItem
{
	Data item;
	ListItem *next = NULL, *prev = NULL;
};

struct List
{
	ListItem *head = NULL;
};

List *list_create()
{
	List* list = new List; 
	list->head = NULL;
    return list;
}

void list_delete(List *list)
{
	ListItem *item_next;
	while (list->head)
	{
		item_next = list->head->next;
		delete list->head;
		list->head = item_next;
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
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
	ListItem* new_list_item = new ListItem;
	new_list_item->item = data;
	new_list_item->next = list->head;
	if (list->head)
	{
		list->head->prev = new_list_item;
	}
	list->head = new_list_item;
	return new_list_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
	ListItem *new_list_item = new ListItem;
	new_list_item->item = data;
	new_list_item->next = item->next;
	if (item->next)
	{
		item->next->prev = new_list_item;
	}
	item->next = new_list_item;
    return new_list_item;
}

ListItem *list_erase(List *list, ListItem *item)
{
	if (item->prev && item->next)
	{
		item->prev->next = item->next;
		item->next->prev = item->prev;
	}
	else if (item->next)
	{ 
		list->head = item->next;
		item->next->prev = item->prev;
	}
	else if (item->prev)
	{
		item->prev->next = item->next;
	}
	else
	{
		list->head = NULL;
	}
	ListItem* item_next = item->next;
	delete item;
	return item_next;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    return list_erase(list, item->next);
}
