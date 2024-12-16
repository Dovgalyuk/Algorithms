#include <iostream>
#include "list.h"

struct ListItem {
    Data data;
    ListItem* next;
    ListItem* prev;
};

struct List {
    ListItem* head;
};

List* list_create() {
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List* list) {
    if (list) {
        list_clear(list);
        delete list;
    }
}
void list_clear(List* list) {
    while (!list_empty(list)) {
        list_erase_first(list);
    }
}

bool list_empty(const List* list) {
    return list->head == nullptr;
}

ListItem* list_first(List* list) {
    if (list_empty(list)) {
        std::cout << "Нет списка1";
    }
    return list->head;
}

Data list_item_data(const ListItem* item) {
    if (!item) {
        std::cout <<"Нет элемента1";
    }
    return item->data;
}

ListItem* list_item_next(ListItem* item) {
    return item ? item->next : nullptr;
}

ListItem* list_item_prev(ListItem* item) {
    return item ? item->prev : nullptr;
}

ListItem* list_insert(List* list, Data data) {
    if (!list) {
        std::cout <<"Нет списка2";
    }

    ListItem* NewItem = new ListItem{ data, nullptr, nullptr };

    if (list_empty(list)) {
        NewItem->next = NewItem;
        NewItem->prev = NewItem;
        list->head = NewItem;
    }
    else {
        ListItem* tail = list->head->prev;
        NewItem->next = list->head;
        NewItem->prev = tail;
        tail->next = NewItem;
        list->head->prev = NewItem;
        list->head = NewItem;
    }

    return NewItem;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (!list) {
        std::cout <<"Нет списка3";
    }
    if (!item) {
        std::cout <<"Нет элемента2";
    }

    ListItem* NewItem = new ListItem{ data, nullptr, nullptr };
    NewItem->next = item->next; 
    NewItem->prev = item; 

    item->next->prev = NewItem;
    item->next = NewItem;
    return NewItem;
}

ListItem* list_erase_first(List* list) {
    if (!list) {
        std::cout <<"Нет списка4";
    }
    if (list_empty(list)) {
        std::cout <<"Пустой список1";
    }

    ListItem* to_delete = list->head;

    if (to_delete->next == to_delete) {
        list->head = nullptr;
    }
    else {
        ListItem* tail = to_delete->prev;
        list->head = to_delete->next;
        list->head->prev = tail;
        tail->next = list->head;
    }

    delete to_delete;
    return list->head;
}

ListItem* list_erase_next(List* list, ListItem* item) {
    if (!list) {
        std::cout <<"Нет списка5";
    }
    if (!item || item->next == item) {
        std::cout <<"Нет элемента3";
    }

    ListItem* to_delete = item->next;

    item->next = to_delete->next;

    if (to_delete == list->head) {
        list->head = to_delete->next;
    }

    to_delete->next->prev = item;

    delete to_delete;
    return item->next;
}

ListItem* list_insert_end(List* list, Data data) {
    if (!list) {
        std::cout <<"Нет списка6";
    }

    if (list_empty(list)) {
        return list_insert(list, data);
    }

    ListItem* tail = list->head->prev;
    return list_insert_after(list, tail, data);
}
