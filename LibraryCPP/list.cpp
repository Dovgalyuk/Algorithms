#include <cstddef>
#include <cstdlib> 
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
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void list_delete(List* list)
{
    ListItem* curr = list->head;
    while (curr != nullptr) {
        ListItem* next = curr->next;
        delete curr;
        curr = next;
    }
    delete list;
}

ListItem* list_first(List* list)
{
    return list->head;
}

Data list_item_data(const ListItem* item)
{
    return item->data;
}

ListItem* list_item_next(ListItem* item)
{
    return item->next;
}

ListItem* list_insert(List* list, Data data)
{
    ListItem* newItem = new ListItem{ data, nullptr };
    if (list->head == nullptr) {
        list->head = newItem;
        list->tail = newItem;
    }
    else {
        newItem->next = list->head;
        list->head = newItem;
    }
    return newItem;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (item == nullptr)
        return list_insert(list, data);
    else
    {
        ListItem* toInsert = new ListItem{ data, item->next };
        item->next = toInsert;

        return toInsert;
    }
}


ListItem* list_erase_first(List* list)
{
    if (list->head == nullptr) {
        return nullptr;
    }

    ListItem* item = list->head;
    list->head = item->next;

    if (list->head == nullptr) {
        list->tail = nullptr;
    }

    delete item;
    return list->head;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (item == nullptr || item->next == nullptr) {
        return nullptr;
    }

    ListItem* toRemove = item->next;
    item->next = toRemove->next;

    if (toRemove->next == nullptr) {
        list->tail = item;
    }

    delete toRemove;
    return item->next;
}
