#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
    ListItem *prev;
    List *owner;
};

struct List
{
    ListItem sentinel;
};

List *list_create()
{
    List *list = new List;
    list->sentinel.data = 0;
    list->sentinel.next = &list->sentinel;
    list->sentinel.prev = &list->sentinel;
    list->sentinel.owner = list;
    return list;
    // return new List;
}

void list_delete(List *list)
{
    // TODO: free items
    while (list_first(list) != nullptr)
        list_erase_first(list);

    delete list;
}

ListItem *list_first(List *list)
{
    if (list->sentinel.next == &list->sentinel)
        return nullptr;

    return list->sentinel.next;
    // return NULL;
}

ListItem *list_last(List *list)
{
    if (list->sentinel.prev == &list->sentinel)
        return nullptr;

    return list->sentinel.prev;
    // return NULL;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
    // return (Data)0;
}

ListItem *list_item_next(ListItem *item)
{
    if (item->next == &item->owner->sentinel)
        return nullptr;

    return item->next;
    // return NULL;
}

ListItem *list_item_prev(ListItem *item)
{
    if (item->prev == &item->owner->sentinel)
        return nullptr;

    return item->prev;
    // return NULL;
}

ListItem *list_insert(List *list, Data data)
{
    return list_insert_after(list, nullptr, data);
    // return NULL;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == nullptr)
        item = &list->sentinel;

    ListItem *new_item = new ListItem;
    new_item->data = data;
    new_item->owner = list;

    new_item->next = item->next;
    new_item->prev = item;

    item->next->prev = new_item;
    item->next = new_item;

    return new_item;
    // return NULL;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, nullptr);
    // return NULL;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr)
        item = &list->sentinel;

    ListItem *deleted = item->next;

    if (deleted == &list->sentinel)
        return nullptr;

    item->next = deleted->next;
    deleted->next->prev = item;

    ListItem *result = deleted->next;
    if (result == &list->sentinel)
        result = nullptr;

    delete deleted;
    return result;
    // return NULL;
}
