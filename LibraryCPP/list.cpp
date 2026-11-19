#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
    ListItem *prev;
    bool fake;
};

struct List
{
    ListItem *fictional;
};

List *list_create()
{
    List *list = new List;

    list->fictional = new ListItem;
    list->fictional->fake = true;

    list->fictional->next = list->fictional;
    list->fictional->prev = list->fictional;

    return list;
}

void list_delete(List *list)
{
    if (list == nullptr)
        return;

    ListItem *item = list->fictional->next;

    while (item != list->fictional)
    {
        ListItem *next = item->next;
        delete item;
        item = next;
    }

    delete list->fictional;
    delete list;
}

ListItem *list_first(List *list)
{
    if (list == nullptr || list->fictional->next == list->fictional)
        return nullptr;

    return list->fictional->next;
}

ListItem *list_last(List *list)
{
    if (list == nullptr || list->fictional->prev == list->fictional)
        return nullptr;

    return list->fictional->prev;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if (item == nullptr || item->next->fake)
        return nullptr;

    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    if (item == nullptr || item->prev->fake)
        return nullptr;

    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    return list_insert_after(list, list->fictional, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (list == nullptr)
        return nullptr;

    if (item == nullptr)
        item = list->fictional;

    ListItem *new_item = new ListItem;

    new_item->data = data;
    new_item->fake = false;

    new_item->next = item->next;
    new_item->prev = item;

    item->next->prev = new_item;
    item->next = new_item;

    return new_item;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, nullptr);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (list == nullptr)
        return nullptr;

    if (item == nullptr)
        item = list->fictional;

    ListItem *del = item->next;

    if (del == list->fictional)
        return nullptr;

    ListItem *next = del->next;

    item->next = next;
    next->prev = item;

    delete del;

    if (next == list->fictional)
        return nullptr;

    return next;
}
