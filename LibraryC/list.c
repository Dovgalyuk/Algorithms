#include <stdlib.h>
#include "list.h"

typedef struct ListItem
{
	Data Value;
	ListItem* Next;
	ListItem* Prev;
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

	ListItem* tail = NULL;
	ListItem* item = list->Head;
	if (item != NULL)  tail = list_item_prev(list->Head);

	while (item != NULL) {
		ListItem* next = item->Next;
		if (list->deleter != NULL)
			list->deleter(item->Value);
		else
			free(item->Value);
		free(item);
		if (item != tail)
			item = next;
		else item = NULL;
	}
	free(list);
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
	return item->Prev;
}

ListItem* list_insert(List* list, Data data)
{
	ListItem* newItem = (ListItem*)malloc(sizeof(ListItem));

	newItem->Value = data;

	if (list->Head == NULL) {
		list->Head = newItem;
		newItem->Next = list->Head;
		newItem->Prev = list->Head;
		return newItem;
	}

	newItem->Next = list->Head;
	newItem->Prev = list->Head->Prev;
	list->Head->Prev->Next = newItem;
	list->Head->Prev = newItem;

	list->Head = newItem;
	return newItem;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
	ListItem* newItem = (ListItem*)malloc(sizeof(ListItem));

	newItem->Value = data;

	newItem->Prev = item;
	item->Next->Prev = newItem;
	newItem->Next = item->Next;
	item->Next = newItem;

	return newItem;
}

ListItem* list_erase_first(List* list)
{
	ListItem* first = list->Head;

	if (first == list->Head->Prev) {
		if (list->deleter != NULL)
			list->deleter(first->Value);
		else
			free(first->Value);
		free(first);
		list->Head = NULL;
		return NULL;
	}

	first->Next->Prev = first->Prev;
	first->Prev->Next = first->Next;
	list->Head = first->Next;

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
	forDel->Next->Prev = item;

	if (forDel == list->Head)
		list->Head = forDel->Next;

	if (list->deleter != NULL)
		list->deleter(forDel->Value);
	else
		free(forDel->Value);
	free(forDel);
	return item->Next;
}
