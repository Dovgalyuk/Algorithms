#include <stdlib.h>
#include <cstring>
#include <stdio.h>
#include "list.h"

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

Data list_item_dt(const ListItem* item)
{
	return item->data;
}

Operation list_item_op(const ListItem* item)
{
	return item->operation;
}

ListItem* list_item_next(ListItem* item)
{
	return item->next;
}

void list_insert(List* list, const char* str)
{
	ListItem* new_item = new ListItem;
	if (is_dt(str) == true)
			new_item->data = cast_dt(str);
	if (is_op(str) == true)
			new_item->operation = cast_op(str);
	new_item->next = list_first(list);
	list->first = new_item;
}

void list_insert_after(List* list, ListItem* item, const char* str)
{
	ListItem* new_item = new ListItem;
	if (is_dt(str) == true)
		new_item->data = cast_dt(str);
	if (is_op(str) == true)
		new_item->operation = cast_op(str);
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

void list_delete(List* list)
{
	while (list->first->next != nullptr) //given that last element->next is nullptr
		list_erase_next(list, list->first);
	delete list->first;
	delete list;
}

bool is_dt(const char* str)
{
	const char* temp_num = "0123456789";
	for (int i = 0; i < strlen(str); i++)
	{
		if (!strchr(temp_num, str[i]))
			return false;
	}
	return true;
}

bool is_op(const char* str)
{
	const char* temp_op = "+-/*";
	if (!strchr(temp_op, str[0]) || str[1] != NULL)
		return false;
	else return true;
}

Data cast_dt(const char* str)
{
	return atoi(str);
}

Operation cast_op(const char* str)
{
	return str[0];
}