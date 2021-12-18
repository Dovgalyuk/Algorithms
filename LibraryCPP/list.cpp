#include <stdlib.h>
#include "list.h"

struct ListItem
{
	Data value;
	ListItem* next;
};

struct List
{
	ListItem* head;
};

List* list_create()
{
	List* list = new List;
	list->head = NULL;
	return list;
}

void list_delete(List* list)
{
	ListItem* current = list->head;

	while (current != NULL)
	{
		ListItem* prev = current;
		current = list_item_next(prev);
		delete prev;
	}

	delete list;
}

ListItem* list_first(List* list)
{
	return list->head;
}

Data list_item_data(const ListItem* item)
{
	return item->value;
}

ListItem* list_item_next(ListItem* item)
{
	return item->next;
}

ListItem* list_insert(List* list, Data data)
{
	ListItem* item = new ListItem;
	item->value = data;

	item->next = list->head;
	list->head = item;

	return item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
	ListItem* new_item = new ListItem;
	new_item->value = data;
	new_item->next = item->next;
	item->next = new_item;

	return new_item;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
	ListItem* delete_elem = item->next;
	item->next = delete_elem->next;
	delete delete_elem;

	return NULL;
}

ListItem* list_erase_head(List* list)
{
	ListItem* delete_elem = list->head;
	list->head = list_item_next(list->head);
	delete delete_elem;

	return NULL;
}