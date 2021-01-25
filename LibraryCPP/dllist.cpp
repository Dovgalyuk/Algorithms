#include <stdlib.h>
#include "dllist.h"

struct DLListItem
{
    Data data;
    DLListItem* next;
    DLListItem* prev;
};

struct DLList
{
    DLListItem* head;
};

DLList* list_create()
{
    DLList* list = new DLList;
    list->head = nullptr;
    return list;
}

void list_delete(DLList* list)
{
    DLListItem* current = list->head;

    while (current != nullptr)
    {
        DLListItem* prev = current;
        current = list_item_next(prev);
        list_erase(list, prev);
    }

    delete list;
}

DLListItem* list_first(DLList* list)
{
    return list->head;
}

Data list_item_data(const DLListItem* item)
{
    return item->data;
}

DLListItem* list_item_next(DLListItem* item)
{
    return item->next;
}

DLListItem* list_item_prev(DLListItem* item)
{
    return item->prev;
}

DLListItem* list_insert(DLList* list, Data data)
{
    DLListItem* item = new DLListItem;
    item->data = data;

    if (list->head == nullptr)
    {
        list->head = item;
        list->head->next = item;
        list->head->prev = item;
    }
    else
    {
        item->prev = list->head->prev;
        item->next = list->head;
        list->head->prev->next = item;
        list->head->prev = item;
    }
    list->head = item;

    return item;
}

DLListItem* list_insert_after(DLList* list, DLListItem* item, Data data)
{
    DLListItem* new_item = new DLListItem;
    new_item->data = data;

    new_item->next = item->next;
    new_item->prev = item;
    if (item->next != nullptr)
    {
        item->next->prev = new_item;
    }
    item->next = new_item;

    return new_item;
}

DLListItem* list_erase_first(DLList* list)
{
    DLListItem* delete_item = list->head;
    DLListItem* new_head = list->head->next;

    if (new_head != nullptr)
    {
        delete_item->prev->next = new_head;
        new_head->prev = delete_item->prev;
        list->head = new_head;
    }

    delete delete_item;

    return nullptr;
}

DLListItem* list_erase(DLList* list, DLListItem* item)
{
    DLListItem* item_prev = item->prev;
    DLListItem* item_next = item->next;
    item_next->prev = item_prev;
    item_prev->next = item->next;
    
    if (item == list->head)
    {
        return list_erase_first(list);
    }
    delete item;

    return item_next;
}

DLListItem* list_erase_next(DLList* list, DLListItem* item)
{
    return list_erase(list, item->next);
}

