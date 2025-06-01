#include "list.h"
#include <cstddef>

struct ListItem {
    Data data;
    ListItem* next;
    ListItem* prev;
};

struct List {
    ListItem* sentinel;
};

List* list_create() {
    List* list = new List;
    list->sentinel = new ListItem{0, nullptr, nullptr};
    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;
    return list;
}

void list_delete(List* list) {
    ListItem* current = list->sentinel->next;
    while (current != list->sentinel) {
        ListItem* to_delete = current;
        current = current->next;
        delete to_delete;
    }
    delete list->sentinel;
    delete list;
}

ListItem* list_first(List* list) {
    return list->sentinel->next == list->sentinel ? nullptr : list->sentinel->next;
}

Data list_item_data(const ListItem* item) {
    return item->data;
}

ListItem* list_item_next(ListItem* item) {
    return item->next;
}

ListItem* list_item_prev(ListItem* item) {
    return item->prev;
}

ListItem* list_insert(List* list, Data data) {
    return list_insert_after(list, nullptr, data);
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (item == nullptr) item = list->sentinel;

    ListItem* new_item = new ListItem{data, item->next, item};
    item->next->prev = new_item;
    item->next = new_item;
    return new_item;
}

ListItem* list_erase_first(List* list) {
    return list_erase_next(list, nullptr);
}

ListItem* list_erase_next(List* list, ListItem* item) {
    if (item == nullptr) item = list->sentinel;

    ListItem* to_delete = item->next;
    if (to_delete == list->sentinel)
        return nullptr;

    item->next = to_delete->next;
    to_delete->next->prev = item;
    ListItem* next = to_delete->next;
    delete to_delete;
    return next;
}
