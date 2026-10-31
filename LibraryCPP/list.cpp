#include <cstddef>
#include "list.h"

// Элемент двусвязного списка
struct ListItem
{
    Data data;        // Значение элемента
    ListItem *prev;   // Указатель на предыдущий элемент
    ListItem *next;   // Указатель на следующий элемент
};

// Двусвязный список
struct List
{
    ListItem *head;   // Указатель на первый элемент списка
    ListItem *tail;   // Указатель на последний элемент списка
};

// Создание нового списка
List *list_create()
{
    List *list = new List;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

// Удаление списка и освобождение всей памяти
void list_delete(List *list)
{
    if (!list)
        return;
    ListItem *current = list->head;
    while (current)
    {
        ListItem *next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

// Получение первого элемента списка
ListItem *list_first(List *list)
{
    return list ? list->head : nullptr;
}

// Получение последнего элемента списка
ListItem *list_last(List *list)
{
    return list ? list->tail : nullptr;
}

// Извлечение данных из элемента списка
Data list_item_data(const ListItem *item)
{
    return item ? item->data : (Data)0;
}

// Получение следующего элемента списка
ListItem *list_item_next(ListItem *item)
{
    return item ? item->next : nullptr;
}

// Получение предыдущего элемента списка
ListItem *list_item_prev(ListItem *item)
{
    return item ? item->prev : nullptr;
}

// Вставка нового элемента в начало списка
ListItem *list_insert(List *list, Data data)
{
    if (!list)
        return nullptr;
    ListItem *item = new ListItem;
    item->data = data;
    item->prev = nullptr;
    item->next = list->head;
    if (list->head)
    {
        list->head->prev = item;
    }
    else
    {
        list->tail = item;
    }
    list->head = item;
    return item;
}

// Вставка нового элемента после указанного элемента
// Если item == nullptr, элемент вставляется в начало
ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list)
        return nullptr;
    if (!item)
    {
        return list_insert(list, data);
    }
    ListItem *new_item = new ListItem;
    new_item->data = data;
    new_item->prev = item;
    new_item->next = item->next;
    if (item->next)
    {
        item->next->prev = new_item;
    }
    else
    {
        list->tail = new_item;
    }
    item->next = new_item;
    return new_item;
}

// Удаление первого элемента списка
ListItem *list_erase_first(List *list)
{
    if (!list || !list->head)
        return nullptr;
    ListItem *to_delete = list->head;
    ListItem *next = to_delete->next;
    list->head = next;
    if (next)
    {
        next->prev = nullptr;
    }
    else
    {
        list->tail = nullptr;
    }
    delete to_delete;
    return next;
}

// Удаление элемента, следующего за указанным
// Если item == nullptr, удаляется первый элемент
ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list)
        return nullptr;
    if (!item)
    {
        return list_erase_first(list);
    }
    ListItem *to_delete = item->next;
    if (!to_delete)
        return nullptr;
    ListItem *next = to_delete->next;
    item->next = next;
    if (next)
    {
        next->prev = item;
    }
    else
    {
        list->tail = item;
    }
    delete to_delete;
    return next;
}
