#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
    ListItem *prev;
    List* list;
};

struct List
{
    ListItem *sentinel;
};

List *list_create()
{
    List * list = new List;
    list->sentinel = new ListItem;
    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;
    list->sentinel->list = list;
    return list;
}

void list_delete(List *list)
{
    if (list != NULL) {
        ListItem* current = list->sentinel->next;
        while (current != list->sentinel) {
            ListItem* next = current->next;
            delete current;
            current = next;
        }
        delete list->sentinel;
        delete list;
    }
}

ListItem *list_first(List *list)
{
    if (!list || list->sentinel->next == list->sentinel)
        return NULL;
    return list->sentinel->next;
}

ListItem *list_last(List *list)
{
    if (!list || list->sentinel->prev == list->sentinel)
        return NULL;
    return list->sentinel->prev;
}

Data list_item_data(const ListItem *item)
{
    if (item != NULL) {
        return item->data;
    }
    return (Data)0;
}

ListItem *list_item_next(ListItem *item)
{
    if (!item) {
        return NULL;
    }
    if (item->next == item->list->sentinel)
        return NULL;
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    if (!item) {
        return NULL;
    }
    if (item->prev == item->list->sentinel)
        return NULL;
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    return list_insert_after(list, list->sentinel, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list || !item) {
        return NULL;
    }

    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = item->next;
    newItem->prev = item;
    newItem->list = list;
    item->next->prev = newItem;
    item->next = newItem;

    return newItem;
}

ListItem *list_erase_first(List *list)
{
    if (!list || list->sentinel->next == list->sentinel)
        return NULL;
    return list_erase_next(list, list->sentinel);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list || !item || item->next == list->sentinel)
        return NULL;

    ListItem* toDelete = item->next;
    item->next = toDelete->next;
    toDelete->next->prev = item;
    delete toDelete;

    return item->next == list->sentinel ? NULL : item->next;
}
