#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
    ListItem* prev;
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
    // TODO: free items
    while (list->head != nullptr) {
        list_erase_first(list);
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

    if (list->head != nullptr) {
        list->head->prev = item;
    }
    else {
        list->tail = item;
    }

    list->head = item;
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    new_item->prev = item;

    if (item->next != nullptr) {
        item->next->prev = new_item;
    }
    else {
        list->tail = new_item;
    }

    item->next = new_item;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == nullptr) {
        return nullptr;
    }

    ListItem* next_item = list->head->next;
    delete list->head;

    list->head = next_item;
    if (next_item != nullptr) {
        next_item->prev = nullptr;
    }
    else {
        list->tail = nullptr;
    }

    return next_item;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item->next == nullptr) {
        return nullptr;
    }

    ListItem* next_item = item->next->next;
    delete item->next;

    item->next = next_item;
    if (next_item != nullptr) {
        next_item->prev = item;
    }
    else {
        list->tail = item;
    }

    return next_item;
}
