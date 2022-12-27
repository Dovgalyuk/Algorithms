#include <cstddef>
#include "list.h"

struct ListItem {
    Data data;
    ListItem *next;

    ListItem(Data data, ListItem *next) {
        this->data = data;
        this->next = next;
    }
};

struct List {
    ListItem *head = NULL;
    ListItem *last = NULL;

    ~List() {
        ListItem *current = this->head;
        while (current) {
            ListItem *next = current->next;
            delete current;
            current = next;
        }
    }
};

List *list_create() {
    return new List;
}

void list_delete(List *list) {
    delete list;
}

ListItem *list_first(List *list) {
    return list->head;
}

Data list_item_data(const ListItem *item) {
    return item->data;
}

ListItem *list_item_next(ListItem *item) {
    return item->next;
}

ListItem *list_item_prev(ListItem *item) {
    return NULL;
}

ListItem *list_insert(List *list, Data data) {
    ListItem *new_item = new ListItem(data, NULL);

    new_item->next = list->head;

    if (!list->head) list->last = new_item;

    return list->head = new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data) {
    if (item == nullptr) {
        return list_insert(list, data);
    } else {
        ListItem *new_item = new ListItem(data, item->next);

        if (item == list->last) list->last = new_item;

        return item->next = new_item;
    }
}

ListItem *list_erase(List *list, ListItem *item) {
    //Реализована только часть, тк у меня односвязный список, а не двусвязный
    if (item == list->head) {
        ListItem *next = list_item_next(item);
        if (item == list->last) list->last = 0;
        delete item;
        return list->head = next;
    }

    return NULL;
}

ListItem *list_erase_next(List *list, ListItem *item) {
    if(!item || list->last == item) return NULL;
    auto next = item->next->next;
    delete item->next;
    if (!next) {
        list->last = item;
        item->next = NULL;
    } else {
        item->next = next;
    }
    return next;
}

ListItem *list_last(List *list) {
    return list->last;
}
