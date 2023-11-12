#include <stdlib.h>
#include "list.h"

typedef struct ListItem
{
	Data Value;
	ListItem* Next;
	
} ListItem;

typedef struct List
{
	ListItem* Head;
	
	FFree* deleter;
} List;

List* list_create(FFree f)
{
	List* newList = (List*)malloc(sizeof(List));
	newList->Head = NULL;
	newList->deleter = f;
	return newList;
}

void list_delete(List* list)
{
	ListItem* item = list->Head;

	while (item != NULL) {
		ListItem* next = item->Next;
		if (list->deleter != NULL)
			list->deleter(item->Value);
		else
			free(item->Value);
		free(item);
		
	}

	free(list);
	list = NULL;
}

ListItem* list_first(List* list)
{
	return list->Head;
}

Data list_item_data(const ListItem* item)
{
	if (item == NULL) return (Data)0;
	return item->Value;
}

ListItem* list_item_next(ListItem* item)
{
	return item->Next;
}

ListItem* list_item_prev(ListItem* item)
{
	
}

ListItem* list_insert(List* list, Data data)
{
	ListItem* newItem = (ListItem*)malloc(sizeof(ListItem));

	newItem->Value = data;

	if (list->Head == NULL) {
		list->Head = newItem;
	
		newItem->Next = list->Head;
		
		return newItem;
	}

	newItem->Next = list->Head;
	
	

	list->Head = newItem;
	return newItem;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
	ListItem* newItem = (ListItem*)malloc(sizeof(ListItem));

	newItem->Value = data;

	
	newItem->Next = item->Next;
	item->Next = newItem;

	

	return newItem;
}

ListItem* list_erase_first(List* list)
{
	ListItem* first = list->Head;

	
		free(first->Value);
		free(first);
		list->Head = NULL;
		
		return NULL;
	


	list->Head = list_item_next(first);

	if (list->deleter != NULL)
		list->deleter(first->Value);
	else
		free(first->Value);
	free(first);
	first = NULL;

	return list->Head;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
	ListItem* forDel = item->Next;

	if (item == forDel) {
		if (list->deleter != NULL)
			list->deleter(forDel->Value);
		else
			free(forDel->Value);
		free(forDel);
		list->Head = NULL;
		
		return NULL;
	}

	item->Next = forDel->Next;
	

	if (forDel == list->Head)
		list->Head = forDel->Next;

	if (list->deleter != NULL)
		list->deleter(forDel->Value);
	else
		free(forDel->Value);
	free(forDel);
	return item->Next;
}
