#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
};

struct List
{
    ListItem* head;
    ListItem* tail;
};

List* list_create()
{
    List* list = new List;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void list_delete(List* list)
{
    ListItem* current = list->head;
    while (current != nullptr)
    {
        ListItem* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

ListItem* list_first(List* list)
{
    return list->head;
}

Data list_item_data(const ListItem* item)
{
    return item->data;
}

ListItem* list_item_next(ListItem* item)
{
    return item->next;
}

//ListItem* list_item_prev(ListItem* item)
//{
//
//}

ListItem* list_insert(List* list, Data data)
{
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = list->head;

    if (list->head == nullptr)
    {
        list->tail = newItem;
    }
    list->head = newItem;

    return newItem;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = item->next;

    if (item->next != nullptr)
    {
        item->next = newItem;
    }
    else {
        list->tail = newItem;
    }

    return newItem;
}

ListItem* list_erase_first(List* list)
{
    if (list->head == nullptr)
    {
        return nullptr;
    }

    ListItem* firstItem = list->head;
    list->head = firstItem->next;

    if (list->head == nullptr)
    {
        list->tail = nullptr;
    }

    delete firstItem;
    return list->head;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (item == nullptr || item->next == nullptr)
    {
        return nullptr;
    }

    ListItem* nextItem = item->next;
    item->next = nextItem->next;

    if (item->next == nullptr)
    {
        list->tail = item;
    }

    delete nextItem;
    return item->next;
}
