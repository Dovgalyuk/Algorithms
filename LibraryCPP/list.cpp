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
};

List *list_create()
{
    List* list = new List;
    list->head = new ListItem;
    list->head->next = list->head;
    list->head->data = 0;
    return list;
}

void list_delete(List *list)
{
    if (!list) return;
    while (list_first(list))
        list_erase_first(list);
    delete list->head;
    delete list;
}

ListItem *list_first(List *list)
{
    if (!list) return nullptr;
    if (list->head->next == list->head) return nullptr;
    return list->head->next;
}

ListItem *list_last(List *list)
{
    if (!list) return nullptr;
    if (list->head->next == list->head) return nullptr;

    ListItem* current = list->head->next;
    while (current->next != list->head)
    {
        current = current->next;
    }
    return current;
}

Data list_item_data(const ListItem *item)
{
    if (!item) return (Data)0;
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if (!item) return nullptr;
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    (void)item;
    return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    if (!list) return nullptr;

    ListItem* item = new ListItem;
    item->data = data;
    item->next = list->head->next;
    list->head->next = item;
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list) return nullptr;

    ListItem* prev = item ? item : list->head;

    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = prev->next;
    prev->next = new_item;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (!list) return nullptr;
    if (list->head->next == list->head) return nullptr;

    return list_erase_next(list, list->head);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list) return nullptr;

    ListItem* prev = item ? item : list->head;
    ListItem* target = prev->next;

    if (target == list->head) return nullptr;

    prev->next = target->next;
    ListItem* next = target->next;
    delete target;
    return next;
}
