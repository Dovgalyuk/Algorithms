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
	ListItem* Tail;
	FFree* deleter;
} List;

List* list_create(FFree f)
{
	List* newList = (List*)malloc(sizeof(List));
	newList->Head = NULL;
	newList->Tail = NULL;
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
		if (item != list->Tail)
			item = next;
		else item = NULL;
	}
	list->Head = NULL;
	list->Tail = NULL;
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
	return item->Prev;
}

ListItem* list_insert(List* list, Data data)
{
	ListItem* newItem = (ListItem*)malloc(sizeof(ListItem));

	newItem->Value = data;

	if (list->Head == NULL) {
		list->Head = newItem;
		list->Tail = newItem;
		newItem->Next = list->Head;
		newItem->Prev = list->Tail;
		return newItem;
	}

	newItem->Next = list->Head;
	list->Head->Prev = newItem;
	newItem->Prev = list->Tail;
	list->Tail->Next = newItem;

	list->Head = newItem;
	return newItem;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
	ListItem* newItem = (ListItem*)malloc(sizeof(ListItem));

	newItem->Value = data;

	newItem->Prev = item;
	list_item_next(item)->Prev = newItem;
	newItem->Next = item->Next;
	item->Next = newItem;

	if (item == list->Tail) list->Tail = newItem;

	return newItem;
}

ListItem* list_erase_first(List* list)
{
	ListItem* first = list->Head;

	if (first == list->Tail) {
		if (list->deleter != NULL)
			list->deleter(first->Value);
		else
			free(first->Value);
		free(first);
		list->Head = NULL;
		list->Tail = NULL;
		return NULL;
	}

	list_item_next(first)->Prev = list->Tail;
	list->Tail->Next = list_item_next(first);
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
		list->Tail = NULL;
		return NULL;
	}

	item->Next = forDel->Next;
	list_item_next(forDel)->Prev = item;

	if (forDel == list->Head)
		list->Head = forDel->Next;
	if (forDel == list->Tail)
		list->Tail = item;

	if (list->deleter != NULL)
		list->deleter(forDel->Value);
	else
		free(forDel->Value);
	free(forDel);
	return item->Next;
}
