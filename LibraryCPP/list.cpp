#include "list.h"
#include <stdexcept>

struct ListItem {
    Data data;
    ListItem* next;
    ListItem* prev;

    ListItem(Data d) : data(d), next(nullptr), prev(nullptr) {}
};

struct List {
    ListItem* head;

    List() : head(nullptr) {}
    ~List() {
        while (!list_first(this))
            list_erase_first(this);
    }
};

List* list_create() {
    return new List();
}

void list_delete(List* list) {
    delete list;
}

ListItem* list_first(List* list) {
    return list ? list->head : nullptr;
}

Data list_item_data(const ListItem* item) {
    if (!item) throw std::invalid_argument("Null item");
    return item->data;
}

ListItem* list_item_next(ListItem* item) {
    return item ? item->next : nullptr;
}

ListItem* list_item_prev(ListItem* item) {
    return item ? item->prev : nullptr;
}

ListItem* list_insert(List* list, Data data) {
    return list_insert_after(list, nullptr, data);
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (!list) throw std::invalid_argument("Null list");

    ListItem* newItem = new ListItem(data);

    if (!list->head) {
        newItem->next = newItem;
        newItem->prev = newItem;
        list->head = newItem;
    } else if (!item) {
        ListItem* tail = list->head->prev;
        newItem->next = list->head;
        newItem->prev = tail;
        tail->next = newItem;
        list->head->prev = newItem;
        list->head = newItem;
    } else {
        newItem->next = item->next;
        newItem->prev = item;
        item->next->prev = newItem;
        item->next = newItem;
    }

    return newItem;
}

ListItem* list_erase_first(List* list) {
    return list_erase_next(list, nullptr);
}

ListItem* list_erase_next(List* list, ListItem* item) {
    if (!list || !list->head) return nullptr;

    ListItem* toDelete = item ? item->next : list->head;

    if (toDelete == toDelete->next) {
        list->head = nullptr;
    } else {
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
        if (toDelete == list->head)
            list->head = toDelete->next;
    }

    ListItem* nextItem = toDelete->next;
    delete toDelete;
    return nextItem;
}