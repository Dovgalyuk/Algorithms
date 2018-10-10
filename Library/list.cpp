#include <stdlib.h>
#include "list.h"

struct ListItem
{
	Data item;
	ListItem *next;
	ListItem *prev;
};

struct List
{
	ListItem *head;
};

List *list_create()
{
	List *tmp = new List;
	tmp->head = NULL;
    return tmp;
}

void list_delete(List *list)
{
	ListItem *tmp = (list)->head;
	ListItem *next = NULL;

	while (tmp) {
		next = tmp->next;
		free(tmp);
		tmp = next;
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
	ListItem *tmp = new ListItem;
	tmp->item = data;
	tmp->next = list->head;
	tmp->prev = NULL;
	list->head = tmp;
	return tmp;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
	ListItem *tmp = new ListItem;
	if (item == NULL)
	{
		return NULL;
	}
	tmp->item = data;
	tmp->prev = item;
	tmp->next = item->next;
	if (item->next)
	{
		item->next->prev = tmp;
	}
	item->next = tmp;
	return NULL;
}

ListItem *list_erase(List *list, ListItem *item)
{
	if (item->next) {
		item->next->prev = item->prev;
	}
	if (!item->prev) {
		list->head = item->next;
	}
	free(item);
	return item;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
	return list_erase(list, item->next);
}
