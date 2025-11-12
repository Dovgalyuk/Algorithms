#include "List.h"
#include <cstdlib>

struct List {
    struct ListItem* head;
};

struct ListItem {
    Data data;
    ListItem* next;
};

List* list_create() {
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List* list) {
    while (list->head != nullptr) {
        list_erase_first(list);
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
    if (item == nullptr) return nullptr;
    return item->next;
}

ListItem* list_item_prev(ListItem* item) {
    return nullptr;
}

ListItem* list_insert(List* list, Data data) {
    ListItem* item = new ListItem;
    item->data = data;
    item->next = list->head;
    list->head = item;
    return item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (item == nullptr) {
        return list_insert(list, data);
    }

    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    item->next = new_item;
    return new_item;
}

ListItem* list_erase_first(List* list) {
    if (list->head == nullptr) {
        return nullptr;
    }

    ListItem* item = list->head;
    list->head = item->next;
    ListItem* next_item = list->head;
    delete item;
    return next_item;
}

ListItem* list_erase_next(List* list, ListItem* item) {
    if (item == nullptr) {
        return list_erase_first(list);
    }

    if (item->next == nullptr) {
        return nullptr;
    }

    ListItem* to_delete = item->next;
    item->next = to_delete->next;
    ListItem* next_item = item->next;
    delete to_delete;
    return next_item;
}
