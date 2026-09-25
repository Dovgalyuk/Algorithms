#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* prev;
    ListItem* next;
};

struct List
{
    ListItem* head;
    ListItem* tail;
};

List *list_create()
{
    List* lst = new List;
    lst->head = nullptr;
    lst->tail = nullptr;
    return lst;
}

void list_delete(List *list)
{
    if (list == nullptr)
    {
        return;
    }

    ListItem* curl = list->head;

    while (curl != nullptr)
    {
        ListItem* next = curl->next;
        delete curl;
        curl = next;
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
    return item ? item->next : nullptr;
}

ListItem *list_item_prev(ListItem *item)
{
    return item ? item->prev : nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* item = new ListItem{data, nullptr, list->head};

    if (list->head != nullptr)
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
    if (item == nullptr)
    {
        return list_insert(list, data);
    }

    ListItem* curl = new ListItem{data, item, item->next};

    if (item->next != nullptr)
    {
        item->next->prev = curl;
    }
    else
    {
        list->tail = curl;
    }

    item->next = curl;

    return curl;
}

ListItem *list_erase_first(List *list)
{
    if (!list->head)
    {
        return nullptr;
    }

    ListItem* item = list->head;
    ListItem* next = item->next;

    list->head = next;

    if (next)
    {
        next->prev = nullptr;
    }
    else
    {
        list->tail = nullptr;
    }

    delete item;
    return next;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem* curl = (item == nullptr) ? list->head : item->next;

    if (curl == nullptr)
    {
        return nullptr;
    }

    ListItem* next = curl->next;

    if (curl->prev != nullptr)
    {
        curl->prev->next = curl->next;
    }
    else
    {
        list->head = curl->next;
    }

    if (curl->next != nullptr)
    {
        curl->next->prev = curl->prev;
    }
    else
    {
        list->tail = curl->prev;
    }

    delete curl;
    return next;
}