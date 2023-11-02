#include <cstddef>
#include "list.h"

#include <iostream>

struct ListItem
{
    Data data;
    ListItem *next;
    ListItem *prev;

    ListItem(Data data) : data(data), next(nullptr), prev(nullptr) {}
};

struct List
{
    ListItem *head;
    ListItem *tail;

    List() : head(nullptr), tail(nullptr) {}
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    ListItem *current = list->head;
    while (current != nullptr)
    {
        ListItem *next = current->next;
        delete current;
        current = next;
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

ListItem *list_item_prev(ListItem *item)
{
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *newItem = new ListItem(data);
    if (list->head == nullptr)
    {
        list->head = newItem;
        list->tail = newItem;
    }
    else
    {
        newItem->next = list->head;
        list->head->prev = newItem;
        list->head = newItem;
    }
    return newItem;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == nullptr)
        return list_insert(list, data);

    ListItem *newItem = new ListItem(data);

    newItem->prev = item;
    newItem->next = item->next;
    if (item->next != nullptr)
        item->next->prev = newItem;
    else
        list->tail = newItem;
    item->next = newItem;

    return newItem;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == nullptr)
        return nullptr;

    ListItem *removedItem = list->head;
    list->head = list->head->next;
    if (list->head != nullptr)
        list->head->prev = nullptr;
    else
        list->tail = nullptr;
    delete removedItem;

    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr || item->next == nullptr)
        return nullptr;

    ListItem *removedItem = item->next;
    item->next = item->next->next;
    if (item->next != nullptr)
        item->next->prev = item;
    else
        list->tail = item;
    delete removedItem;

    return item->next;
}