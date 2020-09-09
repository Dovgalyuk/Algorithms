#include <stdlib.h>
#include "list.h"

struct ListItem
{
	ListItem* pNext;
	Data data;
};

struct List
{
	ListItem* pHead;
};

List *list_create()
{
	List* list = new List;
	list->pHead = NULL;
	return list;
}

void list_delete(List *list)
{
	ListItem* currect = list->pHead;
	while (currect != NULL)
	{
		ListItem* temp = currect->pNext;
		delete currect;
		currect = temp;
	}
	delete list;
}

ListItem *list_first(List *list)
{
	return list->pHead;
}

Data list_item_data(const ListItem *item)
{
	return item->data;
}

ListItem *list_item_next(ListItem *item)
{
	return item->pNext;
}

ListItem *list_item_prev(ListItem *item)
{
	// For non single linked list
	return NULL;
}

ListItem *list_insert(List *list, Data data)
{
	ListItem* item = new ListItem;
	item->data = data;
	item->pNext = list->pHead;
	list->pHead = item;
	return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
	ListItem* newItem = new ListItem;
	newItem->data = data;
	newItem->pNext = item->pNext;
	item->pNext = newItem;
	return newItem;
}

ListItem *list_erase(List *list, ListItem *item)
{
	ListItem* currect = list->pHead;
	ListItem* last;
	while (currect != item)
	{
		last = currect;
		currect = currect->pNext;
	}
	last->pNext = currect->pNext;
	return NULL;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
	ListItem* newItem = item->pNext;
	item->pNext = newItem->pNext;
	delete newItem;
	return item;
}
