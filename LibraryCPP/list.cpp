#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
    ListItem *prev;
};

struct List
{
    ListItem *head;
    ListItem *tail;
};

List *list_create()
{
    List * list = new List;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void list_delete(List *list)
{
    if (list != NULL) {
        ListItem *current = list->head;
        while (current != NULL) {
            ListItem *ptr = current->next;
            delete current;
            current = ptr;
        }
        delete list;
    }
}

ListItem *list_first(List *list)
{
    if (list != NULL) {
        return list->head;
    }
    return NULL;
}

ListItem *list_last(List *list)
{
    if (list != NULL) {
        return list->tail;
    }
    return NULL;
}

Data list_item_data(const ListItem *item)
{
    if (item != NULL) {
        return item->data;
    }
    return (Data)0;
}

ListItem *list_item_next(ListItem *item)
{
    if (item != NULL) {
        return item->next;
    }
    return NULL;
}

ListItem *list_item_prev(ListItem *item)
{
    if (item != NULL) {
        return item->prev;
    }
    return NULL;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *item = new ListItem;
    item->data = data;
    item->prev = NULL;

    if (list->head != NULL) {
        item->next = list->head;
        list->head->prev = item;
        list->head = item;
    } else {
        item->next = NULL;
        list->head = item;
        list->tail = item;
    }
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *newItem = new ListItem;
    newItem->data = data;
    ListItem *ptr = item->next;
    newItem->prev = item;
    newItem->next = ptr;
    item->next = newItem;
    if (ptr != NULL) {
        ptr->prev = newItem;
    } else {
        list->tail = newItem;
    }
    return newItem;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == NULL) {
        return NULL;
    }
    ListItem *oldHead = list->head;
    ListItem *ptr = list->head->next;
    if (ptr != NULL) {
        ptr->prev = NULL;
        list->head = ptr;
    } else {
        list->head = NULL;
        list->tail = NULL;
    }
    delete oldHead;
    return ptr;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem *forDelete = item->next;
    if (forDelete != NULL) {
        ListItem *ptr = forDelete->next;
        if (list->tail == forDelete) {
            list->tail = item;
        }
        item->next = ptr;
        if (ptr->prev != NULL) {
            ptr->prev = item;
        }
        delete forDelete;
        return ptr;
    }
    return NULL;
}
