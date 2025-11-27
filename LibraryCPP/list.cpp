#include <cstddef>
#include "list.h"

struct ListItem {
    Data data;
    ListItem *next;
    ListItem *prev;
};

struct List {
    ListItem *head;
    ListItem *tail;
    size_t size;
};

List *list_create() {
    List *list = new List;
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
    return list;
}

void list_delete(List *list) {
    ListItem *current = list->head;
    while (current) {
        ListItem *next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

ListItem *list_first(List *list) {
    return list->head;
}

Data list_item_data(const ListItem *item) {
    return item ? item->data : (Data)0;
}

ListItem *list_item_next(ListItem *item) {
    return item ? item->next : nullptr;
}

ListItem *list_item_prev(ListItem *item) {
    return item ? item->prev : nullptr;
}

ListItem *list_insert(List *list, Data data) {
    ListItem *new_item = new ListItem;
    new_item->data = data;
    new_item->next = list->head;
    new_item->prev = nullptr;
    if (list->head) {
        list->head->prev = new_item;
    } else {
        list->tail = new_item;
    }
    list->head = new_item;
    list->size++;
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data) {
    if (!item && !list->head) {  // Вставка в пустой список
        return list_insert(list, data);
    }
    ListItem *new_item = new ListItem;
    new_item->data = data;
    new_item->next = item ? item->next : nullptr;
    new_item->prev = item;
    if (item) {
        item->next = new_item;
    } else {
        list->head = new_item;
    }
    if (new_item->next) {
        new_item->next->prev = new_item;
    } else {
        list->tail = new_item;
    }
    list->size++;
    return new_item;
}

ListItem *list_erase_first(List *list) {
    if (!list->head) return nullptr;
    ListItem *deleted = list->head;
    list->head = deleted->next;
    if (list->head) {
        list->head->prev = nullptr;
    } else {
        list->tail = nullptr;
    }
    delete deleted;
    list->size--;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item) {
    ListItem *to_delete = item ? item->next : list->head;
    if (!to_delete) return item ? item->next : nullptr;
    if (to_delete->prev) {
        to_delete->prev->next = to_delete->next;
    } else {
        list->head = to_delete->next;
    }
    if (to_delete->next) {
        to_delete->next->prev = to_delete->prev;
    } else {
        list->tail = to_delete->prev;
    }
    ListItem *next_item = to_delete->next;
    delete to_delete;
    list->size--;
    return next_item;
}
ListItem *list_insert_end(List *list, Data data) {
    return list_insert_after(list, list->tail, data);
}