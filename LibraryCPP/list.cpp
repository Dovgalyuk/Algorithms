
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
    return new List{nullptr, nullptr};
}

void list_delete(List *list)
{
    if (list == nullptr)
    {
        return;
    }

    ListItem *item = list->head;

    while (item != nullptr)
    {
        ListItem *next = item->next;
        delete item;
        item = next;
    }

    delete list;
}

ListItem *list_first(List *list)
{
    return list == nullptr ? nullptr : list->head;
}

ListItem *list_last(List *list)
{
    return list == nullptr ? nullptr : list->tail;
}

Data list_item_data(const ListItem *item)
{
    return item == nullptr ? Data{} : item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item == nullptr ? nullptr : item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    (void)item;
    return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    if (list == nullptr)
    {
        return nullptr;
    }

    ListItem *item = new ListItem{data, list->head};
    list->head = item;

    if (list->tail == nullptr)
    {
        list->tail = item;
    }

    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (list == nullptr)
    {
        return nullptr;
    }

    if (item == nullptr)
    {
        return list_insert(list, data);
    }

    ListItem *new_item = new ListItem{data, item->next};
    item->next = new_item;

    if (list->tail == item)
    {
        list->tail = new_item;
    }

    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list == nullptr || list->head == nullptr)
    {
        return nullptr;
    }

    ListItem *item = list->head;
    list->head = item->next;

    if (list->head == nullptr)
    {
        list->tail = nullptr;
    }

    ListItem *next = item->next;
    delete item;

    return next;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (list == nullptr)
    {
        return nullptr;
    }

    if (item == nullptr)
    {
        return list_erase_first(list);
    }

    ListItem *deleted = item->next;

    if (deleted == nullptr)
    {
        return nullptr;
    }

    item->next = deleted->next;

    if (list->tail == deleted)
    {
        list->tail = item;
    }

    ListItem *next = deleted->next;
    delete deleted;

    return next;
}
