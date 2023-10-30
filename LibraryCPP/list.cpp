#include "list.h"
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
    while (list->head) {
        ListItem* next = list->head->next;
        delete list->head;
        list->head = next;
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

ListItem* list_insert_after(List*, ListItem* item, Data data) {
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = item->next;
    item->next = newItem;
    return newItem;
}

ListItem* list_erase_first(List* list) {
    if (list->head == nullptr) return nullptr;

    ListItem* nextItem = list->head->next;
    delete list->head;
    list->head = nextItem;
    return nextItem;
}

ListItem* list_erase_next(List*, ListItem* item) {
    if (item->next == nullptr) return nullptr;

    ListItem* itemToDelete = item->next;
    item->next = itemToDelete->next;
    delete itemToDelete;
    return item->next;
}