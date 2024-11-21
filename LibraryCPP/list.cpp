#include "list.h"
#include <iostream>

struct ListItem {
    Data data;
    ListItem* next;
    ListItem* prev;
};

struct List {
    ListItem* head;
    ListItem* tail;
};

List* list_create() {
    List* list = new List;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void list_delete(List* list) {
    while (list->head) {
        list_erase_first(list);
    }
    delete list;
}

void list_insert(List* list, Data data) {
    ListItem* newItem = new ListItem{data, nullptr, list->tail};
    if (list->tail) {
        list->tail->next = newItem;
    } else {
        list->head = newItem;
    }
    list->tail = newItem;
}

void list_insert_after(List* list, ListItem* item, Data data) {
    if (!item) return;
    ListItem* newItem = new ListItem{data, item->next, item};
    if (item->next) {
        item->next->prev = newItem;
    } else {
        list->tail = newItem;
    }
    item->next = newItem;
}

void list_erase_first(List* list) {
    if (list->head) {
        ListItem* toDelete = list->head;
        list->head = list->head->next;
        if (list->head) {
            list->head->prev = nullptr;
        } else {
            list->tail = nullptr;
        }
        delete toDelete;
    }
}

ListItem* list_last(const List* list) {
    return list->tail;
}

Data list_item_data(ListItem* item) {
    return item->data;
}

ListItem* list_first(const List* list) {
    return list->head;
}

ListItem* list_item_next(ListItem* item) {
    return item ? item->next : nullptr;
}