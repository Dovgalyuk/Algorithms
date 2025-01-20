#include "list.h"
#include <cstddef> // для nullptr

List* list_create() {
    List* list = new List;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void list_delete(List* list) {
    if (!list) return;
    ListItem* current = list->head;

    if (current) {
        do {
            ListItem* next = current->next;
            delete current;
            current = next;
        } while (current != list->head); // Удаляем до тех пор, пока не вернёмся к head
    }

    delete list;
}

void list_insert(List* list, int data) {
    if (!list) return;

    ListItem* new_item = new ListItem{ data, nullptr, nullptr };

    if (!list->head) {
        // Если список пуст, создаём первый элемент
        list->head = new_item;
        list->tail = new_item;
        new_item->next = new_item; // Указывает на себя
        new_item->prev = new_item; // Указывает на себя
    }
    else {
        // Вставка перед головой
        new_item->next = list->head;
        new_item->prev = list->tail;
        list->head->prev = new_item;
        list->tail->next = new_item;
        list->head = new_item;
    }
}

void list_insert_after(List* list, ListItem* item, int data) {
    if (!list || !item) return;

    ListItem* new_item = new ListItem{ data, nullptr, nullptr };

    new_item->next = item->next;
    new_item->prev = item;

    item->next->prev = new_item;
    item->next = new_item;

    if (item == list->tail) {
        // Если вставляем после хвоста, обновляем tail
        list->tail = new_item;
    }
}

void list_erase_first(List* list) {
    if (!list || !list->head) return;

    ListItem* to_delete = list->head;

    if (list->head == list->tail) {
        // Если в списке один элемент
        list->head = nullptr;
        list->tail = nullptr;
    }
    else {
        list->head = to_delete->next;
        list->tail->next = list->head;
        list->head->prev = list->tail;
    }

    delete to_delete;
}

ListItem* list_first(const List* list) {
    return list ? list->head : nullptr;
}

int list_item_data(const ListItem* item) {
    return item ? item->data : 0;
}

ListItem* list_item_next(const ListItem* item) {
    return item ? item->next : nullptr;
}