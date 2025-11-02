#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
    ListItem* prev;
    ListItem() : data(0), next(nullptr), prev(nullptr) {}
};

struct List
{
    ListItem* head;
    ListItem* tail;
    List() : head(nullptr), tail(nullptr) {}
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    ListItem* cursor = list->head;
    while (cursor)
    {
        ListItem* next = cursor->next;
        delete cursor;
        cursor = next;
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
    ListItem* node = new ListItem;
    node->data = data;

    node->next = list->head;

    if (list->head != nullptr)
        list->head->prev = node;
    else
        list->tail = node;

    list->head = node;

    return node;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem* node = new ListItem;
    node->data = data;
    
    if (item == nullptr) {
        node->next = list->head;
        if (list->head) {
            list->head->prev = node;
        }
        else {
            list->tail = node;
        }
        list->head = node;
        return node;
    }

    node->prev = item;
    node->next = item->next;

    if (item->next) {
        item->next->prev = node;
    }
    else {
        list->tail = node;
    }
    item->next = node;

    return node;
}

ListItem *list_erase_first(List *list)
{
    if (!list || !list->head) return nullptr;

    ListItem* node = list->head->next;
    delete list->head;
    list->head = node;

    if (list->head == nullptr)
    {
        list->tail = nullptr;
    }

    return node;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list || (!item && !list->head)) return nullptr;

    if (item == nullptr) {
        return list_erase_first(list);
    }

    ListItem* node = item->next;
    if (!node) return nullptr;

    item->next = node->next;

    if (node->next) {
        node->next->prev = item;
    }
    else {
        list->tail = item;
    }

    delete node;

    return item->next;
}
