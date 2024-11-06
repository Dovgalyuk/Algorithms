#include <cstddef>
#include "list.h"
#include <stdexcept>

struct ListItem
{
    Data value;
    ListItem* next = nullptr;
    ListItem* prev = nullptr;
};

struct List
{
    ListItem* first = nullptr;
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    if (!list) {
        throw std::invalid_argument("The list pointer is nullptr");
    }

    while (list->first) {
        list_erase_first(list);
    }
    delete list;
}

ListItem *list_first(List *list)
{
    if (!list) {
        throw std::invalid_argument("The list pointer is nullptr");
    }

    return list->first;
}

Data list_item_data(const ListItem *item)
{
    if (!item) {
        throw std::invalid_argument("The item pointer is nullptr");
    }

    return item->value;
}

ListItem *list_item_next(ListItem *item)
{
    if (!item) {
        throw std::invalid_argument("The item pointer is nullptr");
    }

    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    if (!item) {
        throw std::invalid_argument("The item pointer is nullptr");
    }

    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    if (!list) {
        throw std::invalid_argument("The list pointer is nullptr");
    }

    ListItem* ptr = new ListItem;
    ptr->value = data;
    ptr->next = list->first;
    ptr->prev = nullptr;

    if (list->first) {
        list->first->prev = ptr;
    }

    list->first = ptr;

    return ptr;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list) {
        throw std::invalid_argument("The list pointer is nullptr");
    }
    if (!item) {
        throw std::invalid_argument("The item pointer is nullptr");
    }

    ListItem* ptr = new ListItem;
    ptr->value = data;
    ptr->next = item->next;
    ptr->prev = item;

    if (item->next){
        item->next->prev = ptr;
    }

    item->next = ptr;

    return ptr;
}

ListItem *list_erase_first(List *list)
{
    if (!list) {
        throw std::invalid_argument("The list pointer is nullptr");
    }
    if (!(list->first)) {
        throw std::invalid_argument("The list is empty");
    }

    ListItem* ptr;
    ptr = list->first->next;
    if (ptr) {
        ptr->prev = nullptr;
    }
    delete(list->first);
    list->first = ptr;

    return list->first;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list) {
        throw std::invalid_argument("The list pointer is nullptr");
    }
    if (!item) {
        throw std::invalid_argument("The item pointer is nullptr");
    }
    if (item->next == nullptr) {
        throw std::invalid_argument("The item does not have the following element");
    }

    ListItem* ptr;
    ptr = item->next->next;
    if (ptr) {
        ptr->prev = item;
    }
    delete(item->next);
    item->next = ptr;

    return ptr;
}
