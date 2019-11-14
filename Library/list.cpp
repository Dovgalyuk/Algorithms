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

List* list_create()
{
	List* temp = new List;
	temp->start = NULL;
	return temp;
}

void list_delete(List* list)
{
	list->start->prev->next = NULL;
	ListItem* temp = list->start;
	while (temp != NULL)
	{
		temp = list_item_next(list->start);
		delete list->start;
		list->start = temp;
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

ListItem* list_item_prev(ListItem* item)
{
	return item->prev;
}

ListItem* list_insert(List* list, Data data)
{
	if (list->start == NULL) {
		list->start->next = list->start->prev = list->start = new ListItem;;
	}
	else {
		ListItem* head = list->start;
		list->start  = new ListItem;

		list->start->prev = head->prev;
		list->start->next = head;
		head->prev->next = list->start;
		head->prev = list->start;
	}
	list->start->item = data;	
	return list->start;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
		ListItem* head = item->next;
		item->next = new ListItem;
		item->next->item = data;

		head->prev = item->next;
		item->next->next = head;
		item->next->prev = item;
		return item->next;
}

ListItem* list_erase(List* list, ListItem* item)
{
	ListItem* temp_next = item->next;
	ListItem* temp_prev = item->prev;
	if (list->start == list->start->prev) {
		delete item;
		list->start = NULL;
		return list->start;
	}
	else {
		delete item;
		if (item == list->start) {
			list->start = temp_next;
		}
		temp_next->prev = temp_prev;
		temp_prev->next = temp_next;
	}
	return temp_next;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
	return list_erase(list, item->next);
}
