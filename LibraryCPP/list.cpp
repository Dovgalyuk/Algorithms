#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next = nullptr;
    ListItem* prev = nullptr;
};

struct List
{
    ListItem* head = nullptr;
    ListItem* tail = nullptr;
};

List *list_create()
{
    List* list = new List;
    list->head;
    list->tail;
    return list;
}

void list_delete(List *list)
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

ListItem* list_item_next(ListItem *item)
{
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = list->head;
    new_item->prev = nullptr;

    if (list->head) list->head->prev = new_item;
    else
        list->tail = new_item;

    list->head = new_item;
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!item) return list_insert(list, data);

    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->prev = item;
    new_item->next = item->next;

    if (item->next) item->next->prev = new_item;
    else
        list->tail = new_item;

    item->next = new_item;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    ListItem* f_delete = list->head;
    list->head = f_delete->next;

    if (list->head) list->head->prev = nullptr;
    else
        list->tail = nullptr;

    delete f_delete;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!item) return list_erase_first(list);

    ListItem* n_delete = item->next;
    if (!n_delete) return nullptr;

    item->next = n_delete->next;
    if (n_delete->next) n_delete->next->prev = item;
    else
        list->tail = item;

    delete n_delete;
    return item->next;
}