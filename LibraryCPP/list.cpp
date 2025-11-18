#include <cstddef>
#include "list.h"

// пустая реализация структуры ListItem и List
struct ListItem {
    // заглушка, можно добавить поля позже
};

struct List {
    // заглушка, можно добавить поля позже
};

// Создать список
List* list_create() {
    return new List;
}

// Удалить список
void list_delete(List* list) {
    delete list;
}

// Вернуть первый элемент
ListItem* list_first(List* list) {
    (void)list;
    return nullptr;
}

// Получить данные элемента
Data list_item_data(const ListItem* item) {
    (void)item;
    return 0;
}

// Вернуть следующий элемент
ListItem* list_item_next(ListItem* item) {
    (void)item;
    return nullptr;
}

// Вернуть предыдущий элемент
ListItem* list_item_prev(ListItem* item) {
    (void)item;
    return nullptr;
}

// Вставка элемента в начало списка
ListItem* list_insert(List* list, Data data) {
    (void)list;
    (void)data;
    return nullptr;
}

// Вставка после указанного элемента
ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    (void)list;
    (void)item;
    (void)data;
    return nullptr;
}

// Удалить первый элемент
ListItem* list_erase_first(List* list) {
    (void)list;
    return nullptr;
}

// Удалить элемент после указанного
ListItem* list_erase_next(List* list, ListItem* item) {
    (void)list;
    (void)item;
    return nullptr;
}
