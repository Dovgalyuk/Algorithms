#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next = nullptr;
};

struct List
{
    ListItem* head = nullptr;
};

List* list_create()
{
    return new List;
}

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

ListItem* list_first(List* list)
{
    return list->head;
}

ListItem* list_last(List* list)
{
    if (list->head == nullptr) return nullptr;

    ListItem* current = list->head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    return current;
}

Data list_item_data(const ListItem* item)
{
    return item ? item->data : (Data)0;
}

ListItem* list_item_next(ListItem* item)
{
    return item ? item->next : nullptr;
}

ListItem* list_item_prev(ListItem* item)
{
    (void)item;
    return nullptr;
}

// Вставка в начало списка (работает за O(1))
ListItem* list_insert(List* list, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = list->head;
    list->head = new_item;
    return new_item;
}

// Вставка после указанного элемента
ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (item == nullptr)
    {
        return list_insert(list, data);
    }
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    item->next = new_item;
    return new_item;
}

// Удаление первого элемента (работает за O(1))
ListItem* list_erase_first(List* list)
{
    if (list->head == nullptr) return nullptr;

    ListItem* temp = list->head;
    list->head = list->head->next;
    delete temp;
    return list->head;
}

// Удаление элемента ПОСЛЕ указанного
ListItem* list_erase_next(List* list, ListItem* item)
{
    if (item == nullptr)
    {
        return list_erase_first(list);
    }
    if (item->next == nullptr)
    {
        return nullptr;
    }

    ListItem* temp = item->next;
    item->next = temp->next;
    delete temp;
    return item->next;
}