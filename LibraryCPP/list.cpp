#include <cstddef>
#include <iostream>
#include "list.h"

List *list_create()
{
    List* list = new List;
    list->head = list->tail = nullptr;
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
    
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = list->head;
    new_item->prev = nullptr;
    if (list->head != nullptr) {
        list->head->prev = new_item;
    }
    list->head = new_item;
    if (list->tail == nullptr) {
        list->tail = new_item;
    }
    return new_item;
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
    item->next = new_item;
    if (list->tail == item) {
        list->tail = new_item;
    }
    return new_item;

}

ListItem *list_erase_first(List *list)
{
    if (list->head == nullptr) return nullptr;

    ListItem* temp = list->head->next;
    delete list->head;
    list->head = temp;

    if (list->head != nullptr) {
        list->head->prev = nullptr;
    } else {
        list->tail = nullptr;
    }
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr || list->head == nullptr) return nullptr;

    ListItem* temp = item->next->next;
    delete item->next;
    item->next = temp;

    if (item->next != nullptr) {
        item->next->prev = item;
    } else {
        list->tail = item;
    }
    return item->next;
}

void list_print(const List *list) {
    ListItem* current = list->head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}