##include <cstddef>
#include "list.h"

struct ListItem {
    Data data;
    ListItem *next;
    ListItem *prev;
};

struct List {
    ListItem *head;
    ListItem *tail;
};

List *list_create() {
    List *list = new List;
    list->head = nullptr;
    list->tail = nullptr;
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
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data) {
    //  item == nullptr -> вставка в начало
  
    if (!item) {
        return list_insert(list, data);
    }

    ListItem *new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    new_item->prev = item;

    if (item->next) {
        item->next->prev = new_item;
    } else {
        list->tail = new_item;
    }
    item->next = new_item;
    
    return new_item;
}

ListItem *list_erase_first(List *list) {
    if (!list->head) return nullptr;

    ListItem *deleted = list->head;
    ListItem *next_item = deleted->next; 

    list->head = next_item;
    if (list->head) {
        list->head->prev = nullptr;
    } else {
        list->tail = nullptr;
    }

    delete deleted;
    return next_item;
}

ListItem *list_erase_next(List *list, ListItem *item) {
    
    if (!item) return list_erase_first(list);

    ListItem *to_delete = item->next;
    if (!to_delete) return nullptr; // nullptr

    ListItem *next_item = to_delete->next;
    
    if (next_item) {
        next_item->prev = item;
    } else {
        list->tail = item;
    }
    item->next = next_item;

    delete to_delete;
    return next_item;
}

ListItem* list_insert_end(List *list, Data data) {
    return list_insert_after(list, list->tail, data);
}