#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
};

struct List
{
    ListItem *head = nullptr;
    ListItem *tail = nullptr;
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    while (list->head)
    {
        list_erase_first(list);
    }
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
    return item->next;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *newItem = new ListItem;
    newItem->data = data;
    newItem->next = list->head;

    if (!list->head)
    {
        list->tail = newItem;
    }

    list->head = newItem;

    return newItem;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *newItem = new ListItem;
    newItem->data = data;
    newItem->next = item->next;

    if (!item)
    {
        return list_insert(list, data);
    }

    if (!item->next)
    {
        list->tail = newItem;
    }

    item->next = newItem;

    return newItem;
}

ListItem *list_erase_first(List *list)
{
    if (!list->head)
    {
        return nullptr;
    }

    ListItem *newItem = list->head->next;
    delete list->head;
    list->head = newItem;

    if (!newItem)
    {
        list->tail = nullptr;
    }

    return newItem;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!item || !item->next)
    {
        return nullptr;
    }

    ListItem *itemDelete = item->next;
    ListItem *nextItem = itemDelete->next;
    delete itemDelete;

    item->next = nextItem;
    if (!nextItem)
    {
        list->tail = item;
    }

    return nextItem;
}