#include "list.h"

struct ListItem {
    Data data;
    ListItem* next;
    ListItem* prev;
};

struct List {
    ListItem* head;
    ListItem* tail;
};

List* list_create() {
    List* list = new List;
    list->head = nullptr;
    list->tail = nullptr;
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

ListItem* list_item_prev(ListItem* item) {
    return item->prev;
}

ListItem* list_insert(List* list, Data data) {
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = list->head;
    newItem->prev = nullptr;

    if (list->head) {
        list->head->prev = newItem;
    } else {
        list->tail = newItem;
    }

    list->head = newItem;
    return newItem;
}


ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (!item) {
        return nullptr;
    }

    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = item->next;
    newItem->prev = item;

    if (item->next) {
        item->next->prev = newItem;
    } else {
        list->tail = newItem;
    }

    item->next = newItem;
    return newItem;
}

ListItem* list_erase_first(List* list) {
    if (!list->head) {
        return nullptr;
    }

    ListItem* nextItem = list->head->next;
    delete list->head;

    if (nextItem) {
        nextItem->prev = nullptr;
    } else {
        list->tail = nullptr;
    }

    list->head = nextItem;
    return nextItem;
}

ListItem* list_erase_next(List* list, ListItem* item) {
    if (!item || !item->next) {
        return nullptr;
    }

    ListItem* itemToDelete = item->next;
    item->next = itemToDelete->next;

    if (itemToDelete->next) {
        itemToDelete->next->prev = item;
    } else {
        list->tail = item;
    }

    delete itemToDelete;
    return item->next;
}
