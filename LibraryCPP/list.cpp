#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
    ListItem *prev;
};

struct List
{
    ListItem *first = nullptr;
    ListItem *last = nullptr;
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    if (list == nullptr)
        return;

    while (list->first != nullptr)
    {
        list_erase_first(list);
    }

    delete list;
}

ListItem *list_first(List *list)
{
    return list->first;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *item = new ListItem;

    item->data = data;
    item->prev = nullptr;
    item->next = list->first;

    if (list->first != nullptr)
    {
        list->first->prev = item;
    }
    else
    {
        list->last = item;
    }

    list->first = item;

    return item;
}

ListItem *list_erase_first(List *list)
{
    if (list->first == nullptr)
        return nullptr;

    ListItem *item = list->first;

    list->first = item->next;

    if (list->first != nullptr)
    {
        list->first->prev = nullptr;
    }
    else
    {
        list->last = nullptr;
    }

    delete item;

    return list->first;
}
