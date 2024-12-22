#include <cstddef>
#include "list.h"  // Ваш заголовочный файл

// Определение структуры ListItem
struct ListItem {
    Data data;
    ListItem* next;
    ListItem* prev;

    // Конструктор для ListItem с параметрами
    ListItem(Data data, ListItem* next = nullptr, ListItem* prev = nullptr)
        : data(data), next(next), prev(prev) {}
};

// Определение структуры List
struct List {
    ListItem* head;
};

// Создание нового списка
List* list_create() {
    List* list = new List;
    list->head = nullptr;
    return list;
}

// Удаление списка и всех его элементов
void list_delete(List* list) {
    if (!list) return;
    ListItem* current = list->head;
    if (current) {
        do {
            ListItem* next = current->next;
            delete current;
            current = next;
        } while (current != list->head);  // Пока не вернемся к началу списка
    }
    delete list;
}

// Получение первого элемента списка
ListItem* list_first(List* list) {
    return list ? list->head : nullptr;
}

// Получение данных из элемента списка
Data list_item_data(const ListItem* item) {
    return item ? item->data : Data();  // Возвращаем "пустые" данные по умолчанию
}

// Получение следующего элемента для указанного
ListItem* list_item_next(ListItem* item) {
    return item ? item->next : nullptr;
}

// Получение предыдущего элемента для указанного
ListItem* list_item_prev(ListItem* item) {
    return item ? item->prev : nullptr;
}

// Вставка нового элемента в список
ListItem* list_insert(List* list, Data data) {
    if (!list) return nullptr;
    ListItem* new_item = new ListItem(data);
    if (!list->head) {
        new_item->next = new_item->prev = new_item;
        list->head = new_item;
    } else {
        ListItem* tail = list->head->prev;
        new_item->next = list->head;
        new_item->prev = tail;
        tail->next = new_item;
        list->head->prev = new_item;
    }
    return new_item;
}


// Вставка нового элемента после указанного
ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (!list || !item) return nullptr;
    ListItem* new_item = new ListItem(data, item->next, item);
    item->next->prev = new_item;
    item->next = new_item;
    return new_item;
}

// Удаление первого элемента
ListItem* list_erase_first(List* list) {
    if (!list || !list->head) return nullptr;
    ListItem* head = list->head;
    if (head->next == head) {
        list->head = nullptr;
    } else {
        ListItem* tail = head->prev;
        list->head = head->next;
        list->head->prev = tail;
        tail->next = list->head;
    }
    delete head;
    return list->head;
}

// Удаление элемента, следующего за указанным
ListItem* list_erase_next(List* list, ListItem* item) {
    if (!list || !item) return nullptr;
    ListItem* to_delete = item->next;
    if (to_delete) {
        item->next = to_delete->next;
        if (to_delete->next) {
            to_delete->next->prev = item;
        }
        if (to_delete == list->head) {
            list->head = to_delete->next;
        }
        delete to_delete;
    }
    return item->next;
}
