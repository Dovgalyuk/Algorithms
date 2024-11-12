#include "list.h"
#include <stdexcept>

struct ListItem {
    Data data;
    ListItem *next;
    ListItem *prev;
};

struct List {
    ListItem *head;
};

List *list_create() {
    List *list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List *list) {
    while (list->head != nullptr) {
        ListItem *temp = list->head;
        list->head = list->head->next;
        delete temp;
    }
    delete list;
}

ListItem *list_first(List *list) {
    return list->head;
}

Data list_item_data(const ListItem *item) {
    if (item == nullptr) {
        throw std::runtime_error("List item is null");
    }
    return item->data;
}

ListItem *list_item_next(ListItem *item) {
    if (item == nullptr) {
        throw std::runtime_error("List item is null");
    }
    return item->next;
}

ListItem *list_item_prev(ListItem *item) {
    if (item == nullptr) {
        throw std::runtime_error("List item is null");
    }
    return item->prev;
}

ListItem *list_insert(List *list, Data data) {
    ListItem *newItem = new ListItem;
    newItem->data = data;
    newItem->next = list->head;
    newItem->prev = nullptr;

    if (list->head != nullptr) {
        list->head->prev = newItem;
    }

    list->head = newItem;
    return newItem;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data) {
    if (item == nullptr) {
        throw std::runtime_error("List item is null");
    }

    ListItem *newItem = new ListItem;
    newItem->data = data;
    newItem->next = item->next;
    newItem->prev = item;

    if (item->next != nullptr) {
        item->next->prev = newItem;
    }

    item->next = newItem;
    return newItem;
}

ListItem *list_erase_first(List *list) {
    if (list->head == nullptr) {
        throw std::runtime_error("List is empty");
    }

    ListItem *temp = list->head;
    list->head = list->head->next;

    if (list->head != nullptr) {
        list->head->prev = nullptr;
    }

    delete temp;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item) {
    if (item == nullptr || item->next == nullptr) {
        throw std::runtime_error("List item or next item is null");
    }

    ListItem *temp = item->next;
    item->next = item->next->next;

    if (item->next != nullptr) {
        item->next->prev = item;
    }

    delete temp;
    return item->next;
}
