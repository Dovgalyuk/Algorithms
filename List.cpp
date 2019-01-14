#include <stdlib.h>
#include "list.h"
#include <string>

typedef int Data;


struct ListItem
{
	int weight = 0;
	int data;
	ListItem *next;
};

struct List
{
	ListItem *first;
};

List *list_create()
{
	List *list_new = new List();
	list_new->first = nullptr;
	return list_new;
}


void list_delete(List *list)
{
	if (!list->first) {
		delete list;
	}
	else {
		ListItem *tmp1 = list->first, *tmp2;
		while (tmp1 != nullptr)
		{
			tmp2 = tmp1->next;
			list->first = tmp2;
			delete tmp1;
			tmp1 = tmp2;
		}
		delete list;
	}
}

ListItem *list_first(List *list)
{
	return list->first;
}

Data *list_item_data(ListItem *item)
{
		return &item->data;
}

Data *list_item_weight(List *list, Data value)
{
	if (list->first) {
		ListItem *tmp = new ListItem;
		tmp = list->first;
		while (tmp->data != value) {
			if (tmp->next) tmp = tmp->next;
			else return 0;
		}
		return &tmp->weight;
	}
	else return 0;
}

ListItem *list_item_next(ListItem *item)
{
	return item->next;
}

ListItem *list_insert(List *list, Data data)
{
	ListItem *list_new = new ListItem;
	list_new->data = data;
	list_new->weight = 1;
	if (list->first != nullptr)
	{
		list_new->next = list->first;
		list->first = list_new;
	}
	else
	{
		list->first = list_new;
		list_new->next = nullptr;
	}
	return list_new;
}

ListItem *list_erase_first(List *list)
{
	ListItem *list_new = list->first;
	if (list->first->next) {
		list->first = list->first->next;
		delete list_new;
	}
	else {
		list->first = nullptr;
		delete list_new;
	}
	return list->first;
}

ListItem *list_erase_item(List *list, Data value) {
	if (!list->first) return list->first;
	ListItem *tmp = new ListItem;
	tmp = list->first;
	if (tmp->data == value && !tmp->next) {
		list->first = nullptr;
		delete tmp;
		return list->first;
	}
	else if (tmp->data == value && tmp->next) {
		list->first = tmp->next;
		delete tmp;
		return list->first;
	}
	else {
		tmp = list->first->next;
	}
	ListItem *prev = new ListItem;
	prev = list->first;
	while (tmp->data != value) {
		if (tmp->next) { tmp = tmp->next; prev = prev->next; }
		else break;
	}
	if (tmp->next != nullptr) {
		prev->next = tmp->next;
		tmp->next = nullptr;
		delete tmp;
	}
	else {
		prev->next = nullptr;
		delete tmp;
	}
	return list->first;
}

bool list_item_exist(List *list, Data value) {
	if (!list->first) return false;
	ListItem *tmp = list->first;
	while (tmp->data != value) {
		if (!tmp->next) return false;
		tmp = tmp->next;
	}
	return true;
}
