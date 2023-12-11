#include <cstddef>
#include "list.h"
#include <new> 
#include <string>

struct ListItem
{
    std::string data;
    ListItem* next;
    ListItem* prev;
};

struct List
{
    ListItem* head;
    ListItem* tail;
};

List* list_create()
{
    List* list = new List;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
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

std::string list_item_data(const ListItem* item)
{
    return item->data;
}

ListItem* list_item_next(ListItem* item)
{
    return item->next;
}

ListItem* list_item_prev(ListItem* item)
{
    return item->prev;
}

ListItem* list_insert(List* list, std::string data)
{
    ListItem* item = new ListItem{ data, nullptr, nullptr };
    if (list->head == nullptr)
    {
        list->head = item;
        list->tail = item;
    }
    else
    {
        item->next = list->head;
        list->head->prev = item;
        list->head = item;
    }
    return item;
}

ListItem* list_insert_after(List* list, ListItem* item, std::string data)
{
    if (item == nullptr)
        return nullptr;

    ListItem* new_item = new(std::nothrow) ListItem{ data, nullptr, nullptr };
    if (new_item == nullptr)
        return nullptr;

    new_item->next = item->next;
    new_item->prev = item;

    if (item->next != nullptr)
        item->next->prev = new_item;
    else
        list->tail = new_item;

    item->next = new_item;
    return new_item;
}

ListItem* list_erase_first(List* list)
{
    if (list->head == nullptr)
        return nullptr;

    ListItem* item = list->head;
    list->head = item->next;
    if (list->head != nullptr)
        list->head->prev = nullptr;
    else
        list->tail = nullptr;

    delete item;
    return list->head;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (item == nullptr || item->next == nullptr)
        return nullptr;

    ListItem* to_remove = item->next;
    item->next = to_remove->next;

    if (to_remove->next != nullptr)
        to_remove->next->prev = item;
    else
        list->tail = item;

    delete to_remove;
    return item->next;
}
