#include "list.h"

struct ListItem {
    Data data;
    ListItem* next;
    ListItem* prev;
};

struct List {
    ListItem* head;
};

List *list_create() {
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List *list) {
    if (!list->head) {
        delete list;
        return;
    }

    ListItem* current = list->head;
    ListItem* next_item = nullptr;

    do {
        next_item = current->next; 
        delete current; 
        current = next_item;
    } while (current != list->head);

    delete list;
}

ListItem *list_first(List *list) {
    if (list == nullptr) {
        return nullptr;
    }

    return list->head;
}

Data list_item_data(const ListItem *item) {
    return item->data;
}

ListItem *list_item_next(ListItem *item) {
    return item ? item->next : nullptr;
}

ListItem *list_item_prev(ListItem *item) {
    return item ? item->prev : nullptr;
}

ListItem *list_insert(List *list, Data data) {
    if (!list) {
        return nullptr;
    }

    ListItem* new_item = new ListItem{ data, nullptr, nullptr };

    if (list->head == nullptr) {
        new_item->next = new_item;
        new_item->prev = new_item;
        list->head = new_item;
    }
    else {
        ListItem* tail = list->head->prev;
        new_item->next = list->head;
        new_item->prev = tail;
        tail->next = new_item;
        list->head->prev = new_item;
        list->head = new_item;
    }
 
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data) {
    if (!list || !item) {
        return nullptr;
    }

    ListItem* new_item = new ListItem{ data, nullptr, nullptr };

    new_item->next = item->next;
    new_item->prev = item;

    item->next->prev = new_item;
    item->next = new_item;

    return new_item;
}

ListItem *list_erase_first(List *list) {
    if (!list || !list->head) {
        return nullptr;
    }

    ListItem* first_delete = list->head;

    if (first_delete->next == first_delete) {
        list->head = nullptr;
    }
    else {
        ListItem* tail = first_delete->prev;
        list->head = first_delete->next;
        list->head->prev = tail;
        tail->next = list->head;
    }

    delete first_delete;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item) {
    if (!item || item->next == item || !list) {
        return nullptr;
    }

    ListItem* element_delete = item->next;

    item->next = element_delete->next;

    element_delete->next->prev = item;

    if (element_delete == list->head) {
        list->head = element_delete->next;
    }
   
    delete element_delete;
    return item->next;
}

ListItem* list_insert_end(List* list, Data data) {
    if (!list) {
        return nullptr;
    }
    
    ListItem* new_item = new ListItem;

    new_item->data = data;

    if (list->head == nullptr) {
        list->head = new_item;
        new_item->next = new_item;
        new_item->prev = new_item;
    }
    else {
        ListItem* tail = list->head->prev;

        tail->next = new_item; 
        new_item->prev = tail;
        new_item->next = list->head;
        list->head->prev = new_item;
    }

    return new_item;
}
