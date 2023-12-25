#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next = NULL;
};

struct List
{
    ListItem* head = NULL;
    ListItem* tail = NULL;
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    ListItem* current = list->head;
    while (current != NULL) {
		ListItem* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list->head;
}

ListItem* list_tail(List* list)
{
    return list->tail;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
	return item->next;
}

//ListItem *list_item_prev(ListItem *item)
//{
//    return NULL;
//}

ListItem *list_insert(List *list, Data data)
{
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = list->head;
	list->head = newItem;
    if (list->tail == NULL) {
        list->tail = newItem;
    }

    return newItem;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == NULL) {
        return list_insert(list, data);
    }

    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = item->next;
    item->next = newItem;

    if (list->tail == item) {
        list->tail = newItem;
    }

    return newItem;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == NULL) {
        return NULL;
    }
	ListItem* item = list->head;
    list->head = item->next;
    if (list->tail == item) {
        list->tail = NULL;
    }
    delete item;
    return list->head;
}

ListItem* list_erase_tail(List* list)
{
    ListItem* item = list->head;
    if (item == NULL) {
        return NULL;
    }

    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
        delete item;
        return NULL;
    }
    while (item->next != list->tail) {
        item = item->next;
    }

    item->next = NULL;
    delete list->tail;
    list->tail = item;
    return item;
}

ListItem *list_erase_next(List* list, ListItem *item)
{
    if (item == NULL || item->next == NULL) {
        return NULL;
    }

    ListItem* itemDel = item->next;
    item->next = itemDel->next;

    if (itemDel->next == NULL) {
        list->tail = item;
    }

    delete itemDel;
    return item->next;
}
