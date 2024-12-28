#include "list.h"
#include <cstddef> // для NULL
#include <cstdlib> // для malloc/free

List* list_create() {
    List* list = new List;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void list_delete(List* list) {
    ListItem* current = list->head;
    while (current) {
        ListItem* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

void list_insert(List* list, int data) {
    ListItem* new_item = new ListItem{ data, nullptr, nullptr };
    if (!list->head) {
        list->head = new_item;
        list->tail = new_item;
    }
    else {
        new_item->next = list->head;
        list->head->prev = new_item;
        list->head = new_item;
    }
}

void list_insert_after(List* list, ListItem* item, int data) {
    if (!item) return;
    ListItem* new_item = new ListItem{ data, nullptr, nullptr };
    new_item->next = item->next;
    new_item->prev = item;

    if (item->next) {
        item->next->prev = new_item;
    }
    else {
        list->tail = new_item;
    }
    item->next = new_item;
}

void list_erase_first(List* list) {
    if (!list->head) return;

    ListItem* to_delete = list->head;
    list->head = list->head->next;

    if (list->head) {
        list->head->prev = nullptr;
    }
    else {
        list->tail = nullptr;
    }
    delete to_delete;
}

ListItem* list_first(const List* list) {
    return list->head;
}

int list_item_data(const ListItem* item) {
    return item ? item->data : 0;
}

ListItem* list_item_next(const ListItem* item) {
    return item ? item->next : nullptr;
}