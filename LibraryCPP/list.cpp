#include <stdlib.h>
#include "list.h"

List* list_create()
{
	return new List;
}

ListItem* list_first(List* list)
{
	return list->first;
}

Data list_item_data(const ListItem* item)
{
	return item->data;
}

ListItem* list_item_next(ListItem* item)
{
	return item->next;
}

ListItem* list_item_prev(ListItem* item, List *list)
{
	ListItem* temp = list->first;
	while (true)
	{
		if (item == list->first)
		{
			return NULL;
		}		
		else if (temp->next != item)
			temp = temp->next;
		else return temp;
	}
}

ListItem* list_insert(List* list, Data data)
{
	ListItem* new_item = new ListItem;
	new_item->data = data;
	new_item->next = list_first(list);
	list->first = new_item;
	return new_item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
	ListItem* new_item = new ListItem;
	new_item->data = data;
	new_item->next = list_item_next(item);
	item->next = new_item;
	return new_item;
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

void list_erase(List* list, ListItem* item)
{
	if (item == list_first(list)) //deleting first element
	{
		if (list_item_next(item) != nullptr)
		{
			ListItem* temp = list_first(list);
			list->first = list_item_next(list_first(list));
			delete temp;
		}
		else
		{
			delete item;
			item = nullptr;
		}
	}
	else if (list_item_next(item) == nullptr) //deleting last element
	{
		ListItem* temp = list_item_prev(item, list);
		temp->next = nullptr;
		delete item;
	}
	else
	{
		list_erase_next(list, list_item_prev(item, list));
	}
}

void list_delete(List* list)
{
	while (list_item_next(list_first(list)) != nullptr) //given that last element->next is nullptr
		list_erase_next(list, list_first(list));
	list_erase(list, list_first(list));
	delete list;
	list = nullptr;
}