#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *prev;
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
    ListItem *curr = list->head;
    while (curr)
    {
        ListItem *next = curr->next;
        delete curr;
        curr = next;
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
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *item = new ListItem;
    item->data = data;
    item->prev = NULL;
    item->next = list->head;

    if (list->head)
    {
        list->head->prev = item;
    }
    else
    {
        list->tail = item;
    }
    list->head = item;

    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!item)
    {
        return list_insert(list, data);
    }

    ListItem *newItem = new ListItem;
    newItem->data = data;
    newItem->prev = item;
    newItem->next = item->next;

    if (item->next)
    {
        item->next->prev = newItem;
    }
    else
    {
        list->tail = newItem;
    }
    item->next = newItem;

    return newItem;
}

ListItem *list_erase_first(List *list)
{
    if (!list->head)
        return NULL;

    ListItem *to_delete = list->head;
    ListItem *next_item = to_delete->next;

    list->head = next_item;
    if (next_item)
    {
        next_item->prev = NULL;
    }
    else
    {
        list->tail = NULL;
    }

    delete to_delete;
    return next_item;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!item)
    {
        return list_erase_first(list);
    }

    ListItem *to_delete = item->next;
    if (!to_delete)
        return NULL;

    ListItem *next_item = to_delete->next;
    item->next = next_item;

    if (next_item)
    {
        next_item->prev = item;
    }
    else
    {
        list->tail = item;
    }

    delete to_delete;
    return next_item;
}
