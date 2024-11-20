#include <stdexcept>
#include "list.h"
#include "stack.h"

struct ListItem
{
    Data value;
    ListItem* next = nullptr;
};

struct List
{
    ListItem* first = nullptr;
};

List* list_create()
{
    return new List;
}

void list_delete(List* list)
{
    if (!list) {
        throw std::invalid_argument("List nullptr");
    }
    while (list->first) {
        list_erase_first(list);
    }
    delete list;
}

ListItem* list_first(List* list)
{
    if (!list) {
        throw std::invalid_argument("List nullptr");
    }

    return list->first;
}

Data list_item_data(const ListItem* item)
{
    if (!item) {
        throw std::invalid_argument("Item nullptr");
    }

    return item->value;
}

ListItem* list_item_next(ListItem* item)
{
    if (!item) {
        throw std::invalid_argument("Item nullptr");
    }
    return item->next;
}

ListItem* list_insert(List* list, Data data)
{
    if (!list) {
        throw std::invalid_argument("List nullptr");
    }

    ListItem* pointer = new ListItem;
    pointer->value = data;
    pointer->next = list->first;

    list->first = pointer;

    return pointer;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (!list || !item) {
        throw std::invalid_argument("List or Item nullptr");
    }

    ListItem* temp = item->next;
    ListItem* pointer = new ListItem;
    pointer->value = data;
    pointer->next = temp;
    item->next = pointer;

    return pointer;
}

ListItem* list_erase_first(List* list)
{
    if (!list) {
        throw std::invalid_argument("List nullptr");
    }
    ListItem* pointer = list->first;
    list->first = list->first->next;
    delete pointer;

    return list->first;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (!list || !item || !item->next) {
        throw std::invalid_argument("List or Item nullptr");
    }
    ListItem* pointer = item->next;
    item->next = item->next->next;
    delete pointer;

    return item->next;
}