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
    ListItem *head;
    ListItem *tail;
};

List *list_create()
{
    List *list = new List;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void list_delete(List *list)
{
    ListItem *current = list->head;
    while (current != nullptr) {
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
    ListItem *item_insert = new ListItem;
    item_insert->data = data;
    item_insert->next = list->head;
    item_insert->prev = nullptr;

    if (list->head != nullptr) list->head->prev = item_insert;
    else list->tail = item_insert;

    list->head = item_insert;
    return item_insert;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == nullptr) return nullptr;
    ListItem *insert_after = new ListItem;
    insert_after->data = data;
    insert_after->next = item->next;
    insert_after->prev = item;

    if (item->next != nullptr) item->next->prev = insert_after;
    else list->tail = insert_after;

    item->next = insert_after;
    return insert_after;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == nullptr) return nullptr;

    ListItem *item_delete = list->head;
    list->head = item_delete->next;

    if (list->head != nullptr) list->head->prev = nullptr;
    else list->tail = nullptr;

    delete item_delete;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr || item->next == nullptr) return nullptr;

    ListItem *item_delete = item->next;
    item->next = item_delete->next;

    if (item_delete->next != nullptr) item_delete->next->prev = item;
    else list->tail = item;

    delete item_delete;
    return item->next;
}