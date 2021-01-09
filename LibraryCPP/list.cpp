#include <stdlib.h>
#include "list.h"

struct ListItem
{
	ListItem* pNextItem;
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
	ListItem* crrItem = list->pHead;
	while (crrItem != NULL)
	{
		ListItem* tmpItem = crrItem->pNextItem;
		delete crrItem;
		crrItem = tmpItem;
	}
    delete list;
}

ListItem *list_first(List *list)
{
	return list ? list->pHead : NULL;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item ? item->pNextItem : NULL;
}

ListItem *list_item_prev(ListItem *item)
{
    return NULL;
}

ListItem *list_insert(List *list, Data data)
{
	ListItem* newItem = new ListItem;
	newItem->data = data;
	newItem->pNextItem = list->pHead;
	list->pHead = newItem;
	return newItem;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
	ListItem* newItem = new ListItem;
	newItem->data = data;
	newItem->pNextItem = item->pNextItem;
	item->pNextItem = newItem;
	return newItem;
}

ListItem *list_erase(List *list, ListItem *item)
{
	ListItem* temp = list->pHead;
	ListItem* prevItem = temp;
	while (temp != item)
	{
		prevItem = temp;
		temp = temp->pNextItem;
	}
	if (prevItem == temp)
	{
		list->pHead = temp->pNextItem;
	}
	else
	{
		prevItem->pNextItem = temp->pNextItem;
	}
	delete temp;
	return NULL;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
	ListItem* newItem = item->pNextItem;
	item->pNextItem = newItem->pNextItem;
	delete newItem;
	return item;
}
