#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
    bool is_dummy;
};

struct List
{
    ListItem* dummy;
    ListItem* last;
};

List *list_create()
{
    List* list = new List;

    list->dummy = new ListItem;
    list->dummy->data = 0;
    list->dummy->next = list->dummy;
    list->dummy->is_dummy = true;

    list->last = list->dummy;

    return list;
}

void list_delete(List *list)
{
    while (list->dummy->next != list->dummy) {
        list_erase_first(list);
    }

    delete list->dummy;
    delete list;
}

ListItem *list_first(List *list)
{
    if (list->dummy->next == list->dummy) {
        return nullptr;
    }

    return list->dummy->next;
}

ListItem *list_last(List *list)
{
    if (list->last == list->dummy) {
        return nullptr;
    }

    return list->last;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if (item == nullptr) {
        return nullptr;
    }

    if (item->next->is_dummy) {
        return nullptr;
    }

    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    return NULL;
}

ListItem *list_insert(List *list, Data data)
{
    return list_insert_after(list, nullptr, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == nullptr) {
        item = list->dummy;
    }

    ListItem* new_item = new ListItem;

    new_item->data = data;
    new_item->is_dummy = false;

    new_item->next = item->next;
    item->next = new_item;

    if (list->last == item) {
        list->last = new_item;
    }

    return new_item;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, nullptr);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr) {
        item = list->dummy;
    }

    ListItem* removed = item->next;

    if (removed->is_dummy) {
        return nullptr;
    }

    item->next = removed->next;

    if (list->last == removed) {
        list->last = item;
    }

    delete removed;

    return list_item_next(item);
}
