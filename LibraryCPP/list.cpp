#include <stdlib.h>
#include "list.h"

struct ListItem
{
	ListItem* next;
	ListItem* prev;
	Data value;
};

struct List
{
	ListItem* head;
};

List* list_create()
{
	List* list = new List;
	list->head = nullptr;
	return list;
}

void list_delete(List* list)
{
	delete list->head;
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

ListItem* list_item_prev(ListItem* item)
{
	return item->prev;
}

ListItem* list_insert(List* list, Data data)
{
	ListItem* item = new ListItem;
	item->value = data;

	ListItem* current_head = list->head;
	if (current_head != nullptr) current_head->prev = item;
	item->prev = nullptr;
	item->next = current_head;
	list->head = item;

	return item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
	ListItem* new_item = new ListItem;
	new_item->value = data;

	new_item->next = item->next;
	new_item->prev = item;
	item->next->prev = new_item;
	item->next = new_item;

	return new_item;
}

ListItem* list_erase(List* list, ListItem* item)
{
	ListItem* item_prev = item->prev;
	ListItem* item_next = item->next;
	if (item_next != nullptr)
	{
		item_next->prev = item_prev;
	}
	if (item_prev != nullptr)
	{
		item->prev->next = item->next;
	}
	if (item == list->head)
	{
		list_erase_first(list);
		return nullptr;
	}
	delete item;
	return nullptr;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
	list_erase(list, item->next);
	return nullptr;
}

ListItem* list_erase_first(List* list)
{
	ListItem* delete_item = list->head;
	list->head = list->head->next;

	delete delete_item;
	return nullptr;
}



