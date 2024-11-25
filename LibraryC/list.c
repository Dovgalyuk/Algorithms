#include <stdlib.h>
#include "list.h"

typedef struct ListItem
{
    struct ListItem* next;
    Data data;
} ListItem;

typedef struct List
{
    ListItem* head;
    FFree free_func; // Добавляем указатель на функцию освобождения памяти
} List;

// Функция создания списка
List* list_create(FFree f)
{
    List* list = malloc(sizeof(List));
    if (list) {
        list->head = NULL;
        list->free_func = f; // Инициализация функции освобождения
    }
    return list;
}

// Функция удаления списка
void list_delete(List* list)
{
    ListItem* current = list->head;
    while (current) {
        ListItem* next = current->next;
        if (list->free_func) { // Освобождаем данные, если функция задана
            list->free_func(current->data);
        }
        free(current);
        current = next;
    }
    free(list);
}

// Функция получения первого элемента списка
ListItem* list_first(List* list)
{
    return list->head;
}

// Функция получения данных элемента списка
Data list_item_data(const ListItem* item)
{
    return item->data;
}

// Функция получения следующего элемента списка
ListItem* list_item_next(ListItem* item)
{
    return item->next;
}

// Функция вставки элемента в начало списка
ListItem* list_insert(List* list, Data data)
{
    ListItem* new_item = malloc(sizeof(ListItem));
    if (!new_item) return NULL;

    new_item->data = data;
    new_item->next = list->head;
    list->head = new_item;

    return new_item;
}

// Функция вставки элемента после указанного элемента
ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (!list || !item) return NULL;
    ListItem* newItem = (ListItem*)malloc(sizeof(ListItem));
    if (newItem) {
        newItem->data = data;
        newItem->next = item->next;
        item->next = newItem;
    }
    return newItem;
}

// Функция удаления первого элемента списка
ListItem* list_erase_first(List* list)
{
    if (!list->head) return NULL;

    ListItem* to_delete = list->head;
    list->head = to_delete->next;

    if (list->free_func) { // Освобождаем данные, если функция задана
        list->free_func(to_delete->data);
    }

    free(to_delete);

    return list->head;
}

// Функция удаления следующего элемента после указанного
ListItem* list_erase_next(List* list, ListItem* item)
{
    if (!item || !item->next) return NULL;

    ListItem* to_delete = item->next;
    item->next = to_delete->next;

    if (list->free_func) { // Освобождаем данные, если функция задана
        list->free_func(to_delete->data);
    }

    free(to_delete);

    return item->next;
}
//ListItem *list_item_prev(ListItem *item)
//{
//   return NULL;
//}