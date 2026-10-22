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
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void list_delete(List *list)
{
    if (!list)
        return;

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
    if (!list)
        return nullptr;
    return list->head;
}

ListItem *list_last(List *list)
{
    if (!list)
        return nullptr;
    return list->tail;
}

Data list_item_data(const ListItem *item)
{
    if (!item)
        return (Data)0;
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if (!item)
        return nullptr;
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    if (!item)
        return nullptr;
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    if (!list)
        return nullptr;

    ListItem *item = new ListItem;
    item->data = data;
    item->prev = nullptr;
    item->next = list->head;

    if (list->head)
        list->head->prev = item;
    else
        list->tail = item;

    list->head = item;
    return item;
}

// Вставка после item, если item == nullptr — вставка в начало
ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list)
        return nullptr;

    if (!item)
        return list_insert(list, data);

    ListItem *new_item = new ListItem;
    new_item->data = data;
    new_item->prev = item;
    new_item->next = item->next;

    if (item->next)
        item->next->prev = new_item;
    else
        list->tail = new_item;

    item->next = new_item;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (!list || !list->head)
        return nullptr;

    ListItem *item = list->head;
    list->head = item->next;

    if (list->head)
        list->head->prev = nullptr;
    else
        list->tail = nullptr;

    delete item;
    return list->head;
}

// Удаляет элемент после item, если item == nullptr — удаляет первый.
ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list)
        return nullptr;

    if (!item)
        return list_erase_first(list);

    ListItem *target = item->next;
    if (!target)
        return nullptr;

    item->next = target->next;

    if (target->next)
        target->next->prev = item;
    else
        list->tail = item;

    delete target;
    return item->next;
}