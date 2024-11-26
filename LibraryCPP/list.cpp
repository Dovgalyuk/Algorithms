#include <cstddef>
#include <iostream>
#include "list.h"

struct ListItem {
    Data data;
    ListItem* next;
    ListItem* prev;
};

struct List {
    ListItem* head;
};

List* list_create()
{
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List* list)
{
    while (list->head != nullptr) {
        list_erase_first(list);
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

ListItem* list_item_prev(ListItem* item)
{
    return item->prev;
}

ListItem* list_insert(List* list, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = list->head;
    new_item->prev = nullptr;

    if (list->head != nullptr) {
        list->head->prev = new_item;
    }

    list->head = new_item;
    return new_item;
}

ListItem* list_insert_after(ListItem* item, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    new_item->prev = item;
    if (item->next != nullptr) {
        item->next->prev = new_item;
    }
    item->next = new_item;

    return new_item;

}

ListItem* list_erase_first(List* list)
{
    if (list->head == nullptr) return nullptr;

    ListItem* temp = list->head->next;
    delete list->head;
    list->head = temp;

    if (list->head != nullptr) {
        list->head->prev = nullptr;
    }

    return list->head;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (item == nullptr || list->head == nullptr) return nullptr;

    ListItem* temp = item->next->next;
    delete item->next;
    item->next = temp;

    if (item->next != nullptr) {
        item->next->prev = item;
    }

    return item->next;
}
