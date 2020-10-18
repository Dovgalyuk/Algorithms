#include <stdlib.h>
#include "list.h"

struct ListItem
{
	Data data;
	ListItem* next;
};

struct List
{
	ListItem* first;
};

List* list_create()
{
	List* new_list = new List;
	new_list->first = new ListItem;
	new_list->first->next = nullptr; //the current element is last
	return new_list;
}

ListItem* list_first(List* list)
{
	return list->first;
}

Data list_get(const ListItem* item)
{
	return item->data;
}

ListItem* list_item_next(ListItem* item)
{
	return item->next;
}

void list_insert(List* list, Data data)
{
	ListItem* new_item = new ListItem;
	new_item->data = data;
	new_item->next = list_first(list);
	list->first = new_item;
}

void list_insert_after(List* list, ListItem* item, Data data)
{
	ListItem* new_item = new ListItem;
	new_item->data = data;
	new_item->next = list_item_next(item);
	item->next = new_item;
}

void list_erase_next(List* list, ListItem* item)
{
	if (list_item_next(item) == nullptr) //if the current element is last
		return;
	else
	{
		ListItem* temp = list_item_next(item);
		item->next = list_item_next(temp);
		delete temp;
	}
}

void list_erase_first(List* list)
{
	if (list->first == nullptr)
		return;
	else
	{
		ListItem* temp = list->first->next;
		delete list->first;
		list->first = temp;
	}
}

void list_delete(List* list)
{
	if (list->first != nullptr)
	{
		while (list->first->next != nullptr)
			list_erase_next(list, list->first);
		list_erase_first(list);
	}
	else
	{
		delete list;
		list = nullptr;
	}
}