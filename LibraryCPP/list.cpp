#include "list.h"
#include <cstddef>
#include <iostream>

struct ListItem {
    Data data;
    ListItem* next;
};

struct List {
    ListItem* head = nullptr;
};

List* list_create() {
    return new List;
}

void list_delete(List* list) {
    while (list->head) {
        ListItem* temp = list->head;
        list->head = list->head->next;
        delete temp;
    }
    delete list;
}

ListItem* list_first(List* list) {
    return list->head;
}

Data list_item_data(const ListItem* item) {
    return item ? item->data : 0;
}

ListItem* list_item_next(ListItem* item) {
    return item ? item->next : nullptr;
}

ListItem* list_insert(List* list, Data data) {
    ListItem* newItem = new ListItem{data, list->head};
    list->head = newItem;
    return newItem;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (!item) return nullptr;

    ListItem* newItem = new ListItem{data, item->next};
    item->next = newItem;
    return newItem;
}

ListItem* list_erase_first(List* list) {
    if (!list->head) return nullptr;

    ListItem* temp = list->head;
    list->head = list->head->next;
    delete temp;
    return list->head;
}

ListItem* list_erase_next(List* list, ListItem* item) {
    if (!item || !item->next) return nullptr;

    ListItem* temp = item->next;
    item->next = temp->next;
    delete temp;
    return item->next;
}