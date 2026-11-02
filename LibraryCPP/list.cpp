#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
    ListItem* prev;
};

struct List
{
    ListItem* head;
    ListItem* tail;
};

List *list_create()
{
    List* list = new List;

    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void list_delete(List *list)
{
    if (list == nullptr)
    {
        return;
    }
    ListItem* item = list->head;

    while (item != nullptr)
    {
        ListItem* next = item->next;

        delete item;

        item = next;
    }

    delete list;
}

ListItem *list_first(List *list)
{
    if (list == nullptr)
    {
        return nullptr;
    }

    return list->head;
}

ListItem *list_last(List *list)
{
    if (list == nullptr)
    {
        return nullptr;
    }

    return list->tail;
}

Data list_item_data(const ListItem *item)
{
    if (item == nullptr)
    {
        return 0;
    }

    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if (item == nullptr)
    {
        return nullptr;
    }

    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    if (item == nullptr)
    {
        return nullptr;
    }

    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    if (list == nullptr)
    {
        return nullptr;
    }

    ListItem* item = new ListItem;

    item->data = data;
    item->prev = nullptr;
    item->next = list->head;

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
    if (list == nullptr)
    {
        return nullptr;
    }

    if (item == nullptr)
    {
        return list_insert(list, data);
    }

    ListItem* new_item = new ListItem;

    new_item->data = data;
    new_item->prev = item;
    new_item->next = item->next;

    if (item->next != nullptr)
    {
        item->next->prev = new_item;
    }
    else
    {
        list->tail = new_item;
    }

    item->next = new_item;

    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list == nullptr || list->head == nullptr)
    {
        return nullptr;
    }

    ListItem* item = list->head;
    ListItem* next = item->next;

    list->head = next;

    if (next != nullptr)
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
    if (list == nullptr)
    {
        return nullptr;
    }

    if (item == nullptr)
    {
        return list_erase_first(list);
    }

    if (item->next == nullptr)
    {
        return nullptr;
    }

    ListItem* deleted = item->next;
    ListItem* next = deleted->next;

    item->next = next;

    if (next != nullptr)
    {
        next->prev = item;
    }
    else
    {
        list->tail = item;
    }

    delete deleted;

    return next;
}
