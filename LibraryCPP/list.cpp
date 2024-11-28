#include <cstddef>
#include "list.h"

struct ListItem {
    Data data;
    ListItem *next;
    ListItem *prev;
};

struct List {
    ListItem *first;
    ListItem *last;
};

List *list_create() {
    List *list = new List;
    list->first = nullptr;
    list->last = nullptr;
    return list;
}

void list_delete(List *list) {
    ListItem *curItem = list->first;

    while(curItem != nullptr) {
        ListItem *nextItem = curItem->next;
        delete curItem;
        curItem = nextItem;
    }
    delete list;
}

ListItem *list_first(List *list) {
    return list->first;
}

Data list_item_data(const ListItem *item) {
    if (item != nullptr) {
        return item->data;
    } else {
        return (Data)0;
    }
}

ListItem *list_item_next(ListItem *item) {
    return item->next;
}

ListItem *list_item_prev(ListItem *item) {
    if (item->prev != nullptr) {
        return item->prev;
    } else {
        return nullptr;
    }
}

ListItem *list_insert(List *list, Data data) {
    ListItem *newItem = new ListItem{data, nullptr, nullptr};  

    if (list->first == nullptr) {
        list->first = newItem;
        list->last = newItem;
    } else {
        newItem->next = list->first;
        list->first->prev = newItem;
        list->first = newItem;
    }

    return newItem;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data) {
    if (item->next == nullptr || item == nullptr) {
        return list_insert(list, data);
    } else {
        ListItem *item_insert = new ListItem{data, item->next, item};
        item->next = item_insert;
        item_insert->next->prev = item_insert;

        return item_insert;
    }
}

ListItem *list_erase_first(List *list) {
    if (list->first == nullptr) {
        return nullptr;
    }

    ListItem *deleteItem = list->first;
    list->first = deleteItem->next;

    if (list->first != nullptr) {
        list->first->prev = nullptr;
    } else {
        list->last = nullptr;
    }

    delete deleteItem;
    return list->first;
}

ListItem *list_erase_next(List *list, ListItem *item) {
    if (item == nullptr || item->next == nullptr) {
        return nullptr;
    }
    ListItem *deleteItem = item->next;
    item->next = deleteItem->next;
    if (deleteItem->next != nullptr) {
        deleteItem->next->prev = item;
    } else {
        list->last = item;
    }
    delete deleteItem;
    return item->next;

}
