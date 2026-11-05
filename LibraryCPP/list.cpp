#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
    ListItem* prev;
    bool fictive;
};

struct List
{
    ListItem* fictive;
};

List* list_create()
{
    List* list = new List;

    list->fictive = new ListItem;
    list->fictive->next = list->fictive;
    list->fictive->prev = list->fictive;
    list->fictive->fictive = true;

    return list;
}

void list_delete(List* list)
{
    if (list == nullptr)
    {
        return;
    }

    ListItem* item = list->fictive->next;

    while (!item->fictive)
    {
        ListItem* next = item->next;
        delete item;
        item = next;
    }

    delete list->fictive;
    delete list;
}

ListItem* list_first(List* list)
{
    if (list->fictive->next->fictive)
    {
        return nullptr;
    }

    return list->fictive->next;
}

ListItem* list_last(List* list)
{
    if (list->fictive->prev->fictive)
    {
        return nullptr;
    }

    return list->fictive->prev;
}

Data list_item_data(const ListItem* item)
{
    return item->data;
}

ListItem* list_item_next(ListItem* item)
{
    if (item->next->fictive)
    {
        return nullptr;
    }

    return item->next;
}

ListItem* list_item_prev(ListItem* item)
{
    if (item->prev->fictive)
    {
        return nullptr;
    }

    return item->prev;
}

ListItem* list_insert(List* list, Data data)
{
    return list_insert_after(list, nullptr, data);
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (item == nullptr)
    {
        item = list->fictive;
    }

    ListItem* newItem = new ListItem;

    newItem->data = data;
    newItem->fictive = false;

    newItem->next = item->next;
    newItem->prev = item;

    item->next->prev = newItem;
    item->next = newItem;

    return newItem;
}

ListItem* list_erase_first(List* list)
{
    return list_erase_next(list, nullptr);
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (item == nullptr)
    {
        item = list->fictive;
    }

    ListItem* deleted = item->next;

    if (deleted->fictive)
    {
        return nullptr;
    }

    ListItem* next = deleted->next;

    item->next = next;
    next->prev = item;

    delete deleted;

    if (next->fictive)
    {
        return nullptr;
    }

    return next;
}