#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;

    ListItem(Data value): data(value), next(nullptr) {}
};

struct List
{
    ListItem *head;

    List() : head(nullptr) {}
};

List *list_create()
{
    List *list = new List();
    list->head = NULL;
    return list;
}

void list_delete(List *list)
{
    // TODO: free items
    ListItem* current = list->head;
    while (current) {
        ListItem* next = current->next;
        delete current; // Освобождаем память текущего элемента
        current = next; // Переход к следующему элементу
    }
    delete list;
}

ListItem *list_first(List *list)
{
   return list->head;
}

Data list_item_data(ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* newItem = new ListItem(data); // Создаем новый элемент
    newItem->next = list->head; // Указываем на текущую голову
    list->head = newItem; // Обновляем голову списка
    return newItem; // Возвращаем указатель на новый элемент
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == nullptr)
        return list_insert(list, data);

    ListItem* newItem = new ListItem(data); // Создаем новый элемент
    newItem->next = item->next; // Указываем на следующий элемент после текущего
    item->next = newItem; // Указываем, что следующий элемент после текущего - это новый
    return newItem;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == nullptr)
        return nullptr; // Если список пуст, ничего не делаем

    ListItem* toErase = list->head; // Запоминаем элемент для удаления
    list->head = list->head->next; // Обновляем голову списка
    delete toErase; // Удаляем элемент
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr || item->next == nullptr)
        return nullptr; // Если элемент null или нет следующего элемента
    ListItem* toErase = item->next;
    item->next = toErase->next;
    delete toErase;
    return item->next;
}

bool list_empty(List *list) {
    return list->head == NULL;
}
ListItem *list_second_to_last(List *list)
{
    // Если список пуст или содержит только один элемент, возвращаем nullptr
    if (list->head == nullptr || list->head->next == nullptr)
    {
        return nullptr;
    }

    ListItem *current = list->head;

    // Ищем предпоследний элемент
    while (current->next->next != nullptr)
    {
        current = current->next; // Переходим к следующему элементу
    }

    // Возвращаем предпоследний элемент
    return current;
}
ListItem *list_last(List *list)
{
    if (list->head == nullptr) // Если список пуст, возвращаем nullptr
        return nullptr;

    ListItem *current = list->head; // Начинаем с головы списка

    // Проходим до конца списка
    while (current->next != nullptr)
    {
        current = current->next; // Переходим к следующему элементу
    }

    // Возвращаем последний элемент
    return current;
}


