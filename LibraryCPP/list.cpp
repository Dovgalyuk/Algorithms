#include "list.h"
#include <cstddef>

// Создание нового списка
List* list_create() {
    List* list = new List;
    list->head = nullptr;
    return list;
}

// Удаление списка и освобождение памяти
void list_delete(List* list) {
    while (list->head != nullptr) {
        ListItem* temp = list->head;
        list->head = list->head->next;
        delete temp;
    }
    delete list;
}

// Получение первого элемента списка
ListItem* list_first(List* list) {
    return list->head;
}

// Получение данных из элемента списка
Data list_item_data(const ListItem* item) {
    return item->data;
}

// Получение следующего элемента списка
ListItem* list_item_next(ListItem* item) {
    return item->next;
}

// Вставка элемента в начало списка
ListItem* list_insert(List* list, Data data) {
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = list->head;
    list->head = newItem;
    return newItem;
}

// Вставка элемента после указанного элемента
ListItem* list_insert_after(List* /*list*/, ListItem* item, Data data) {
    if (item == nullptr) {
        return nullptr; 
    }
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = item->next;
    item->next = newItem;
    return newItem;
}

// Удаление первого элемента списка
ListItem* list_erase_first(List* list) {
    if (list->head == nullptr) {
        return nullptr; 
    }
    ListItem* temp = list->head;
    list->head = list->head->next;
    delete temp;
    return list->head;
}

// Удаление элемента, следующего за указанным
ListItem* list_erase_next(ListItem* item) {
    if (item == nullptr || item->next == nullptr) {
        return nullptr; 
    }
    ListItem* temp = item->next;
    item->next = item->next->next;
    delete temp;
    return item->next;
}