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
    ListItem* head;
    ListItem* tail;
};

List *list_create()
{
    List* list = new List;
    list->head = nullptr;
    list->tail = nullptr;
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

ListItem *list_last(List *list)
{
    return list->tail;
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

ListItem *list_insert_back(List *list, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = nullptr;
    new_item->prev = list->tail;
    
    if (list->tail != nullptr) {
        list->tail->next = new_item;
    }
    list->tail = new_item;
    
    if (list->head == nullptr) {
        list->head = new_item;
    }
    
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == nullptr) {
        return list_insert(list, data);
    }
    
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    new_item->prev = item;
    
    if (item->next != nullptr) {
        item->next->prev = new_item;
    }
    item->next = new_item;
    
    if (item == list->tail) {
        list->tail = new_item;
    }
    
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == nullptr) {
        return nullptr;
    }
    
    ListItem* to_delete = list->head;
    ListItem* next_item = to_delete->next;
    
    if (next_item != nullptr) {
        next_item->prev = nullptr;
    }
    list->head = next_item;
    
    if (list->tail == to_delete) {
        list->tail = nullptr;
    }
    
    delete to_delete;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr) {
        return list_erase_first(list);
    }
    
    if (item->next == nullptr) {
        return nullptr;
    }
    
    ListItem* to_delete = item->next;
    ListItem* next_item = to_delete->next;
    
    item->next = next_item;
    if (next_item != nullptr) {
        next_item->prev = item;
    }
    
    if (list->tail == to_delete) {
        list->tail = item;
    }
    
    delete to_delete;
    return next_item;
}