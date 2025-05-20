#include <cstddef>
#include "list.h"
#include <iostream>

struct ListItem
{
    Data data;
    ListItem *next;
};

struct List
{
    ListItem *head;
};

List *list_create()
{
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List *list)
{
    ListItem* current = list->head;
    while (current != nullptr) {
        ListItem* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    if (list == nullptr) return nullptr;
    return list->head;
}

Data list_item_data(const ListItem *item)
{
    if (item == nullptr) {
        std::cerr << "Error: list_item_data called with null item" << std::endl;
        return 0;
    }
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if (item == nullptr) return nullptr;
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    if (list == nullptr) return nullptr;

    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = list->head;
    list->head = newItem;
    return newItem;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (list == nullptr) return nullptr;

    ListItem* newItem = new ListItem;
    newItem->data = data;

    if (item == nullptr) {
        
        newItem->next = list->head;
        list->head = newItem;
    }
    else {
        newItem->next = item->next;
        item->next = newItem;
    }
    return newItem;
}

ListItem *list_erase_first(List *list)
{
    if (list == nullptr) return nullptr;
    if (list->head == nullptr) return nullptr;

    ListItem* temp = list->head;
    list->head = list->head->next;
    ListItem* next = temp->next;
    delete temp;
    return next;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (list == nullptr) return nullptr;

    ListItem* toDelete;
    ListItem* next;

    if (item == nullptr) {
        
        if (list->head == nullptr) return nullptr;
        toDelete = list->head;
        list->head = list->head->next;
        next = list->head;
    }
    else {
        toDelete = item->next;
        if (toDelete == nullptr) return nullptr;
        item->next = toDelete->next;
        next = item->next;
    }

    delete toDelete;
    return next;
}
