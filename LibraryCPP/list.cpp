#include <cstddef>
#include "list.h"

struct ListItem // структура элемента списка
{
    Data data;
    ListItem* next;
    ListItem* prev;
};

struct List // структура списка
{
    ListItem* head;
};

List *list_create()
{
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List *list)
{
    while (list->head != nullptr)
    {
        list_erase(list, list->head);
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
    ListItem* item = new ListItem;
    item->data = data;
    item->next = list->head;
    item->prev = nullptr;
    if (list->head != nullptr)
    {
        list->head->prev = item;
    }
    list->head = item;
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = item->next;
    newItem->prev = item;
    if (item->next != nullptr)
    {
        item->next->prev = newItem;
    }
    item->next = newItem;
    return newItem;
}

ListItem *list_erase(List *list, ListItem *item)
{
    if (list->head == nullptr)
    {
        return nullptr;
    }
    ListItem* nextItem = nullptr;
    if (item->prev != nullptr)
    {
        item->prev->next = item->next;
        nextItem = item->prev;
    }
    else
    {
        list->head = item->next;
    }
    if (item->next != nullptr)
    {
        item->next->prev = item->prev;
        nextItem = item->next;
    }
    delete item;
    return nextItem;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item->next != nullptr)
    {
        return list_erase(list, item->next);
    }
    return item;
}
