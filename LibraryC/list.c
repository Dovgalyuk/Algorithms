#include <stdlib.h>
#include "list.h"

typedef struct ListItem {
    Data value;
    ListItem *prev;
    ListItem *next;
} ListItem;

typedef struct List {
    FFree *destruct;
    ListItem *head;
} List;

List *list_create(FFree destructor_func) {
    List *new_list = malloc(sizeof(List));
    new_list -> destruct = destructor_func;
    new_list -> head = NULL;
    return new_list;
}

void list_delete(List *list) {
    while (list -> head) {
        list_erase_first(list);
    }
    free(list);
}

ListItem *list_first(List *list) {
    return list -> head;
}

Data list_item_data(const ListItem *item) {
    if (item) {
        return item -> value;
    } else {
        return (Data)0;
    }
}

ListItem *list_item_next(ListItem *item) {
    if (item) {
        return item -> next;
    } else {
        return item;
    }
}

ListItem *list_item_prev(ListItem *item) {
    if (item) {
        return item -> prev;
    } else {
        return item;
    }
}

ListItem *list_insert(List *list, Data data) {
    ListItem *new_item = malloc(sizeof(ListItem));
    new_item -> value = data;
    if (list -> head) {
        new_item -> next = list -> head;
        new_item -> prev = list -> head -> prev;
        new_item -> prev -> next = new_item;
        list -> head -> prev = new_item;
    } else {
        new_item -> next = new_item;
        new_item -> prev = new_item;
    }
    list -> head = new_item;
    return list -> head;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data) {
    ListItem *new_item = malloc(sizeof(ListItem));
    new_item -> value = data;
    new_item -> next = item -> next;
    new_item -> prev = item;
    item -> next = new_item;
    new_item -> next -> prev = new_item;
    return item -> next;
}

ListItem *list_erase_first(List *list) {
    ListItem *temp = NULL;
    if (list -> head) {
        temp = list -> head -> next;

        temp -> prev = list -> head -> prev;
        list -> head -> prev -> next = temp;
        if (list -> destruct) {
            list -> destruct(list -> head -> value);
        }
        free(list -> head);
        if (temp != list -> head){
            list -> head = temp;
        } else {
            list -> head = NULL;
        }
    }
    return list -> head;
}

ListItem *list_erase_next(List *list, ListItem *item) {
    ListItem *temp = NULL;
    if (item) {
        temp = item -> next -> next;
        temp -> prev = item;
        if (list -> destruct) {
            list -> destruct(item -> next -> value);
        }
        free(item -> next);
        item -> next = temp;
    }
    return temp;
}
