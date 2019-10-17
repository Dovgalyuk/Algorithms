#include <stdlib.h>
#include "list.h"

struct ListItem
{
	Data D;
	ListItem *next = NULL;
	ListItem *prev = NULL;
};

struct List
{
	ListItem *head;
};

List *list_create()
{
	List *list = new List;
	list->head = NULL;
	return list;
}

void list_delete(List *list)
{
	ListItem *p = list->head;
	ListItem *next = NULL;
	while (p) {
		next = p->next;
		delete p;
		p = next;
	}
	delete list;
}

ListItem *list_first(List *list)
{
	return list->head;
}

Data list_item_data(const ListItem *item)
{
	return item->D;
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
	ListItem *p = new ListItem;
	p->D = data;
	p->next = list->head;
	if (list->head)
		list->head->prev = p;
	list->head = p;
	return p;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
	ListItem *p = new ListItem;
	if (item == NULL) {
		return NULL;
	}
	p->D = data;
	p->prev = item;
	p->next = item->next;
	if (item->next)
		item->next->prev = p;
	item->next = p;
	return p;
}

ListItem *list_erase(List *list, ListItem *item)
{
	if (item->next && item->prev) {
		item->prev->next = item->next;
		item->next->prev = item->prev;
	}
	else if (item->next) {
		list->head = item->next;
		item->next->prev = NULL;
	}
	else if (item->prev) {
		item->prev->next = NULL;
	}
	else
		list->head = NULL;
	ListItem *next = item->next;
	delete item;
	return next;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
	return list_erase(list, item->next);
}
