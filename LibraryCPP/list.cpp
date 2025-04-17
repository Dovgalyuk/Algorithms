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
    list->head = list->tail = nullptr;
    return list;
}

void list_delete(List* list)
{
    ListItem* current = list->head;
    while (current)
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
    return item ? item->data : 0;
}

ListItem* list_item_next(ListItem* item)
{
    return item ? item->next : nullptr;
}

ListItem* list_insert(List* list, Data data)
{
    ListItem* new_item = new ListItem{ data, list->head };
    list->head = new_item;
    if (!list->tail)
    {
        list->tail = new_item;
    }
    return new_item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (!item)
    {
        return list_insert(list, data);
    }
    ListItem* new_item = new ListItem{ data, item->next };
    item->next = new_item;
    if (list->tail == item)
    {
        list->tail = new_item;
    }
    return new_item;
}

ListItem* list_erase_first(List* list)
{
    if (!list->head)
    {
        return nullptr;
    }
    ListItem* to_delete = list->head;
    list->head = to_delete->next;
    if (!list->head)
    {
        list->tail = nullptr;
    }
    delete to_delete;
    return list->head;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (!item || !item->next)
    {
        return nullptr;
    }
    ListItem* to_delete = item->next;
    item->next = to_delete->next;
    if (list->tail == to_delete)
    {
        list->tail = item;
    }
    delete to_delete;
    return item->next;
}