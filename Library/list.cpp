#include <stdlib.h>
#include "list.h"

struct ListItem
{
	Data item; 
	ListItem* next; 
};

struct List
{
	ListItem* start; 
};

List* list_create()
{
	List* p = new List; 
	p->start = NULL; 
	return p;  
}

void list_delete(List* list)
{
	ListItem* p = list->start; 
	while (p != NULL)
	{
		p = list_item_next(list->start); 
		delete list->start; 
		list->start = p; 
	}
	delete list; 
}

ListItem* list_first(List* list)
{
	return list->start; 
}

Data list_item_data(const ListItem* item)
{
	return item->item; 
}

ListItem* list_item_next(ListItem* item)
{
	return item->next; 
}

ListItem* list_insert(List* list, Data data)
{
	if (list->start == NULL) 
	{
		list->start = new ListItem; 
		list->start->next = NULL; 
	}
	else
	{
		ListItem* p = list->start; 
		list->start = new ListItem; 
		list->start->next = p; 
	}
	list->start->item = data; 
	return list->start; 
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
	ListItem* p = item->next; 
	item->next = new ListItem; 
	item->next->item = data; 
	item->next->next = p; 
	return item->next; 
}

ListItem* list_erase_first(List* list)
{
	ListItem* p = list->start->next; 
	delete list->start; 
	list->start = p; 
	return p; 
}

ListItem* list_erase_next(List* list, ListItem* item)
{
	ListItem* p = item->next->next; 
	delete item->next; 
	item->next = p; 
	return p; 
}
