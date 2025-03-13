#include "list.h"
#include <cstddef>
#include <iostream>

// Узел списка
struct ListItem {
    Data data;
    ListItem* next;
};

// Сам список
struct List {
    ListItem* head = nullptr;
};

// Создание списка
List* list_create() {
    return new List;
}

// Удаление списка
void list_delete(List* list) {
    while (list->head) {
        ListItem* temp = list->head;
        list->head = list->head->next;
        delete temp;
    }
    delete list;
}

// Получить первый элемент списка
ListItem* list_first(List* list) {
    return list->head;
}

// Получить данные элемента
Data list_item_data(const ListItem* item) {
    return item ? item->data : 0;
}

// Получить следующий элемент списка
ListItem* list_item_next(ListItem* item) {
    return item ? item->next : nullptr;
}

// Вставка элемента в начало списка
ListItem* list_insert(List* list, Data data) {
    ListItem* newItem = new ListItem{data, list->head};
    list->head = newItem;
    return newItem;
}

// Вставка после указанного элемента
ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (!item) return nullptr;  // Если item == nullptr, ничего не делаем

    ListItem* newItem = new ListItem{data, item->next};
    item->next = newItem;
    return newItem;
}

// Удаление первого элемента списка
ListItem* list_erase_first(List* list) {
    if (!list->head) return nullptr;

    ListItem* temp = list->head;
    list->head = list->head->next;
    delete temp;
    return list->head;
}

// Удаление элемента после указанного
ListItem* list_erase_next(List* list, ListItem* item) {
    if (!item || !item->next) return nullptr;

    ListItem* temp = item->next;
    item->next = temp->next;
    delete temp;
    return item->next;
}