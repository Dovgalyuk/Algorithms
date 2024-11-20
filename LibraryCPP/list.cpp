#include <cstddef>
#include "list.h"

struct ListItem {
    Data data;
    ListItem* prev;
    ListItem* next;
};

struct List {
    ListItem* head;
    ListItem* tail;
};

// создание двусвязного списка
List *list_create() {
    List* list = new List;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}


void list_delete(List *list) {
    ListItem* current = list->head;
    while (current) {
        ListItem* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}


ListItem *list_first(List *list) {
    return list->head;
}

// данные элемента
Data list_item_data(const ListItem *item) {
    return item->data;
}


ListItem *list_item_next(ListItem *item) {
    return item->next;
}

ListItem *list_item_prev(ListItem *item) {
    return item->prev;
}

// в конец
ListItem *list_insert(List *list, Data data) {
    ListItem* newItem = new ListItem{data, nullptr, nullptr};
    if (!list->head) {
        list->head = newItem;
        list->tail = newItem;
    } else {
        list->tail->next = newItem;
        newItem->prev = list->tail;
        list->tail = newItem;
    }
    return newItem;
}


ListItem *list_insert_after(List *list, ListItem *item, Data data) {
    if (!item) return list_insert(list, data);
    
    ListItem* newItem = new ListItem{data, item, item->next};
    if (item->next) {
        item->next->prev = newItem;
    } else {
        list->tail = newItem;
    }
    item->next = newItem;
    return newItem;
}


ListItem *list_erase_first(List *list) {
    if (!list->head) return nullptr;

    ListItem* itemToDelete = list->head;
    list->head = list->head->next;
    if (list->head) {
        list->head->prev = nullptr;
    } else {
        list->tail = nullptr; // list пуст
    }
    delete itemToDelete;
    return list->head;
}

// удаление след. элемента
ListItem *list_erase_next(List *list, ListItem *item) {
    if (!item || !item->next) return nullptr;

    ListItem* itemToDelete = item->next;
    item->next = itemToDelete->next;
    if (itemToDelete->next) {
        itemToDelete->next->prev = item;
    } else {
        list->tail = item; // если удаляем ласт элемент
    }
    delete itemToDelete;
    return item->next;
}