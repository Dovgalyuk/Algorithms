#include "list.h"

struct ListItem {
    Data value;
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
    while (list->head) {
        ListItem* temp = list->head;
        list->head = temp->next;
        delete temp;
    }
    delete list;
}

ListItem* list_first(List* list) {
    return list->head;
}

Data list_item_data(const ListItem* item) {
    return item->value;
}

ListItem* list_item_next(ListItem* item) {
    return item ? item->next : nullptr;
}

ListItem* list_item_prev() {
    return nullptr;
}

ListItem* list_insert(List* list, Data data) {
    ListItem* newItem = new ListItem;
    newItem->value = data;
    newItem->next = list->head;
    list->head = newItem;
    return newItem;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (item == nullptr) {
        return list_insert(list, data);
    }
    ListItem* newItem = new ListItem;
    newItem->value = data;
    newItem->next = item->next;
    item->next = newItem;
    return newItem;
}

ListItem* list_erase_first(List* list) {
    if (!list->head) return nullptr;
    ListItem* temp = list->head;
    list->head = temp->next;
    delete temp;
    return list->head;
}

ListItem* list_erase_next(List* list, ListItem* item) {
    if (!item) return list_erase_first(list);
    if (!item->next) return nullptr;
    ListItem* del = item->next;
    item->next = del->next;
    delete del;
    return item->next;
}
