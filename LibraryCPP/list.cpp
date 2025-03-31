#include "list.h"
#include <cstddef>


struct ListItem {
    Data data;
    ListItem* next;
};

struct List {
    ListItem* head;
};


List* list_create() {
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List* list) {
    while (list->head != nullptr) {
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
    return item->data;
}

ListItem* list_item_next(ListItem* item) {
    return item->next;
}

ListItem* list_insert(List* list, Data data) {
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = list->head;
    list->head = newItem;
    return newItem;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (!list || !item) return nullptr;
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = item->next;
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

ListItem* list_erase_next(ListItem* item) {
    if (!item || !item->next) return nullptr;
    ListItem* temp = item->next;
    item->next = item->next->next;
    delete temp;
    return item->next;
}