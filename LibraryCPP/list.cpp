#include <cstddef>
#include "list.h"

struct List {
    ListItem* head;
};

struct ListItem {
    Data data;
    ListItem* next;
    ListItem* prev;
};

List* list_create()
{
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List* list)
{
    // TODO: free items
     while (list->head) {
        ListItem* next = list->head->next;
        delete list->head;
        list->head = next;
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

ListItem* list_item_prev(ListItem* item)
{
    return item ? item->prev : nullptr;
}

ListItem* list_insert(List* list, Data data)
{
     ListItem* newItem = new ListItem{data, list->head, nullptr};
    if (list->head) {
        list->head->prev = newItem;
    }
    list->head = newItem;
    return newItem;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
     if (!item) {
        return nullptr;
    }

    ListItem* newItem = new ListItem{data, item->next, item};
    if (item->next) {
        item->next->prev = newItem;
    }
    item->next = newItem;
    return newItem;
}

ListItem* list_erase_first(List* list)
{
    if (!list->head) {
        return nullptr;
    }

    ListItem* next = list->head->next;
    delete list->head;
    list->head = next;

    if (next) {
        next->prev = nullptr;
    }

    return next;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
     if (!item || !item->next) {
        return nullptr;
    }

    ListItem* next = item->next->next;
    delete item->next;
    item->next = next;

    if (next) {
        next->prev = item;
    }

    return next;
}
