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
};

List *list_create()
{
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List *list)
{
    if (!list) return;
    while (list->head) 
    {
        list_erase_first(list);
    }
    delete list;
}

ListItem *list_first(List *list)
{
    if (!list) return nullptr;
    return list->head;
}

Data list_item_data(const ListItem *item)
{
    if (!item) return 0;
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if (!item) return nullptr;
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    if (!item) return nullptr;
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
     if (!list) return nullptr;
    ListItem* new_item = new ListItem;
    new_item->data = data;
    if (!list->head) {
        new_item->next = new_item;
        new_item->prev = new_item;
        list->head = new_item;
    } else {
        ListItem* tail = list->head->prev;
        new_item->next = list->head;
        new_item->prev = tail;
        list->head->prev = new_item;
        tail->next = new_item;
        list->head = new_item;
    }
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list) return nullptr;
    if (!list->head || !item) {
        return list_insert(list, data);
    }
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    new_item->prev = item;
    item->next->prev = new_item;
    item->next = new_item;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, nullptr);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list || !list->head) return nullptr;
    ListItem* to_delete = nullptr;
    if (!item) {
        item = list->head->prev;
        to_delete = list->head;
    } else {
        to_delete = item->next;
    }
    if (to_delete->next == to_delete) {
        list->head = nullptr;
        delete to_delete;
        return nullptr;
    }
    item->next = to_delete->next;
    to_delete->next->prev = item;
    if (to_delete == list->head) {
        list->head = to_delete->next;
    }
    ListItem* result = to_delete->next;
    delete to_delete;
    return result;
}