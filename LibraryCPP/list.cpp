#include <cstddef>
#include <iostream>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
    ListItem* previous;
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
    // TODO: free items
    while (list->head) {
        ListItem *temp = list->head; 
        list->head = list->head->next; 
        delete temp;
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
    return item->previous;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = list->head;
    new_item->previous = nullptr;

    if (list->head) {
        list->head->previous = new_item;
    }

    list->head = new_item;
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    new_item->previous = item;

    if (item->next) {
        item->next->previous = new_item;
    }

    item->next = new_item;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == nullptr) return nullptr;

    ListItem* first_item = list->head->next;
    delete list->head;
    list->head = first_item;

    if (list->head != nullptr) {
        list->head->previous = nullptr;
    }

    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (list->head == nullptr || item == nullptr) return nullptr;

    ListItem* del_item = item->next;
    item->next = item->next->next;

    if (item->next != nullptr) {
        item->next->previous = item;
    }

    delete del_item;
    return item->next;
}
