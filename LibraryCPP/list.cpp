#include <stdlib.h>
#include "list.h"

struct ListItem
{
	ListItem *pNext;
	ListItem *pPrev;
	Data data;
};

struct List
{
	ListItem *head;
};

List *list_create()
{
	List *new_list =new List;
	new_list->head =nullptr;
    return new_list;
}

void list_delete(List *list)
{
	while(list_erase(list, list_first(list)) != nullptr);
    delete list;
}

ListItem *list_first(List *list)
{
    return list->head;
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
    return item->pPrev;
}

ListItem *list_insert(List *list, Data data)
{
	ListItem *new_item =new ListItem;
	new_item->pNext =list->head;
	new_item->pPrev =nullptr;
	new_item->data =data;

	if(list_first(list) !=nullptr)
		list_first(list)->pPrev =new_item;
	list->head =new_item;
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
	ListItem *new_item =new ListItem;
	new_item->pNext =list_item_next(item);
	new_item->pPrev =item;
	new_item->data =data;

	if( list_item_next(item) != nullptr)
		list_item_next(item)->pPrev =new_item;
	item->pNext =new_item;

    return new_item;
}

ListItem *list_erase(List *list, ListItem *item)
{
	if(list_first(list) == nullptr)
		return nullptr;

	ListItem *next_item =nullptr;

	if(item->pPrev != nullptr)
	{
		item->pPrev->pNext =item->pNext;
		next_item =item->pPrev;
	}
	else
	{
		list->head =item->pNext;
	}

	if(item->pNext != nullptr)
	{
		item->pNext->pPrev =item->pPrev;
		next_item =item->pNext;
	}

	delete item;
	return next_item;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
	if(list_item_next(item) != nullptr)
		return list_erase(list, list_item_next(item));
	return item;
}
