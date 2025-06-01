#include "list.h"
#include <cstdlib>

struct ListItem {
    Data data;
    ListItem* next;
    ListItem* prev;
};

struct List {
    ListItem* head;
};

List* list_create() {
    List* list = (List*)malloc(sizeof(List));
    if (list) {
        list->head = nullptr;
    }
    return list;
}

void list_delete(List* list) {
    if (!list) return;
    if (!list->head) {
        free(list);
        return;
    }

    ListItem* current = list->head;
    ListItem* nextItem;

    do {
        nextItem = current->next;
        free(current);
        current = nextItem;
    } while (current != list->head);

    free(list);
}

ListItem* list_first(List* list) {
    return list ? list->head : nullptr;
}

Data list_item_data(const ListItem* item) {
    return item ? item->data : 0;
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
    if (!list) return nullptr;

    ListItem* newItem = (ListItem*)malloc(sizeof(ListItem));
    if (!newItem) return nullptr;

    newItem->data = data;

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

    ListItem* toDelete = nullptr;

    if (!item) {
        toDelete = list->head;
    } else {
        toDelete = item->next;
        if (toDelete == list->head) {
            list->head = toDelete->next;
        }
    }

    if (toDelete == toDelete->next) {
        list->head = nullptr;
        free(toDelete);
        return nullptr;
    } else {
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
        if (list->head == toDelete) {
            list->head = toDelete->next;
        }
        ListItem* nextItem = toDelete->next;
        free(toDelete);
        return nextItem;
    }
}
