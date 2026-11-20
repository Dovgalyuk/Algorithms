#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
};

struct List
{
    ListItem *head;
    ListItem *tail;
};

List *list_create()
{
    List *list = new List;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void list_delete(List *list)
{
    ListItem *item = list->head;
    while (item)
    {
        ListItem *next = item->next;
        delete item;
        item = next;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list->head;
}

ListItem *list_last(List *list)
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

ListItem *list_item_prev(ListItem *item)
{
    (void)item;
    return NULL;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *item = new ListItem;
    item->data = data;
    item->next = list->head;
    list->head = item;
    if (list->tail == NULL)
        list->tail = item;
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == NULL)
        return list_insert(list, data);

    ListItem *new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    item->next = new_item;
    if (list->tail == item)
        list->tail = new_item;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == NULL)
        return NULL;

    ListItem *old = list->head;
    ListItem *next = old->next;
    list->head = next;
    if (list->head == NULL)
        list->tail = NULL;
    delete old;
    return next;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == NULL)
        return list_erase_first(list);

    ListItem *old = item->next;
    if (old == NULL)
        return NULL;

    ListItem *next = old->next;
    item->next = next;
    if (list->tail == old)
        list->tail = item;
    delete old;
    return next;
}