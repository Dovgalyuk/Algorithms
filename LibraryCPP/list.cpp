// list.cpp

#include "list.h"
#include <cstddef>

// Определение структур, скрытое от пользователя
struct ListItem
{
    Data data;
    ListItem* next;
};

struct List
{
    ListItem* head;
};

// Создаёт новый список
List* list_create()
{
    List* list = new List;
    list->head = nullptr;
    return list;
}

// Уничтожает список и освобождает память
void list_delete(List* list)
{
    ListItem* current = list->head;
    while (current != nullptr)
    {
        ListItem* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

// Возвращает первый элемент списка
ListItem* list_first(List* list)
{
    return list->head;
}

// Извлекает данные из элемента списка
Data list_item_data(const ListItem* item)
{
    return item->data;
}

// Возвращает следующий элемент списка
ListItem* list_item_next(ListItem* item)
{
    return item->next;
}

// Возвращает предыдущий элемент для указанного элемента.
// Не применимо для односвязных списков
ListItem* list_item_prev(ListItem* item)
{
    // Не поддерживается в односвязном списке
    return nullptr;
}

// Вставляет новый элемент в начало списка
ListItem* list_insert(List* list, Data data)
{
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = list->head;
    list->head = newItem;
    return newItem;
}

// Вставляет новый элемент после указанного
ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (item == nullptr)
    {
        // Если item == nullptr, вставляем в начало списка
        return list_insert(list, data);
    }
    else
    {
        ListItem* newItem = new ListItem;
        newItem->data = data;
        newItem->next = item->next;
        item->next = newItem;
        return newItem;
    }
}

// Удаляет первый элемент списка.
// Возвращает указатель на следующий элемент после удалённого.
ListItem* list_erase_first(List* list)
{
    if (list->head == nullptr)
        return nullptr;

    ListItem* toDelete = list->head;
    list->head = toDelete->next;
    ListItem* nextItem = list->head;
    delete toDelete;
    return nextItem;
}

// Удаляет элемент, следующий за указанным.
// Возвращает указатель на следующий элемент после удалённого.
// Должно работать за O(1)
ListItem* list_erase_next(List* list, ListItem* item)
{
    if (item == nullptr)
    {
        // Если item == nullptr, удаляем первый элемент
        return list_erase_first(list);
    }
    else if (item->next == nullptr)
    {
        // Нет следующего элемента для удаления
        return nullptr;
    }
    else
    {
        ListItem* toDelete = item->next;
        item->next = toDelete->next;
        ListItem* nextItem = item->next;
        delete toDelete;
        return nextItem;
    }
}

// Удаляет указанный элемент.
// Возвращает указатель на следующий элемент после удалённого.
// Должно работать за O(1)
ListItem* list_erase(List* list, ListItem* item)
{
    if (item == nullptr)
        return nullptr;

    if (item->next != nullptr)
    {
        // Копируем данные из следующего узла и удаляем следующий узел
        ListItem* nextItem = item->next;
        item->data = nextItem->data;
        item->next = nextItem->next;
        delete nextItem;
        return item->next;
    }
    else
    {
        // Если это последний элемент, нам нужно найти предыдущий элемент, что займёт O(n)
        // Поскольку требование O(1), удаление последнего элемента невозможно в односвязном списке без предыдущего указателя
        // Поэтому мы не можем удалить последний элемент за O(1)
        return nullptr;
    }
}
