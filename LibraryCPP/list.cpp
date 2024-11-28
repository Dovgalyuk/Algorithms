#include <stdlib.h>
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

// Creates an empty list
List *list_create() {
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

// Deletes the list
void list_delete(List *list) {
    ListItem *current = list->head;
    while (current) {
        ListItem *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

// Inserts data at the beginning
void list_insert(List *list, Data data) {
    ListItem *item = (ListItem *)malloc(sizeof(ListItem));
    item->data = data;
    item->next = list->head;
    item->prev = NULL;
    if (list->head) {
        list->head->prev = item;
    }
    list->head = item;
    if (!list->tail) {
        list->tail = item;
    }
}

// Inserts data after a given item
void list_insert_after(List *list, ListItem *item, Data data) {
    ListItem *new_item = (ListItem *)malloc(sizeof(ListItem));
    new_item->data = data;
    new_item->next = item->next;
    new_item->prev = item;
    item->next = new_item;
    if (new_item->next) {
        new_item->next->prev = new_item;
    } else {
        list->tail = new_item;
    }
}

// Erases the first item
void list_erase_first(List *list) {
    if (list->head) {
        ListItem *to_delete = list->head;
        list->head = list->head->next;
        if (list->head) {
            list->head->prev = NULL;
        } else {
            list->tail = NULL;
        }
        free(to_delete);
    }
}

// Returns the first item
ListItem *list_first(const List *list) {
    return list->head;
}

// Returns the data of the item
Data list_item_data(const ListItem *item) {
    return item->data;
}

// Returns the next item
ListItem *list_item_next(const ListItem *item) {
    return item->next;
}
