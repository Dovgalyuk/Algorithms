#include <cstddef>
#include "list.h"
#include <stdexcept>

struct ListItem
{
    ListItem *previous_item = nullptr;
    ListItem *next_item = nullptr;
    Data value;
};

struct List
{
    ListItem *first = nullptr;
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    if (!list) throw std::invalid_argument("The list pointer is nullptr");

    while (list->first)
        list_erase_first(list);

    delete list;
}

ListItem *list_first(List *list)
{
    if (!list) throw std::invalid_argument("The list pointer is nullptr");

    return list->first;
}

Data list_item_data(const ListItem *item)
{
    if (!item) throw std::invalid_argument("The item pointer is nullptr");
    return item->value;
}

ListItem *list_item_next(ListItem *item)
{
    if (!item) throw std::invalid_argument("The item pointer is nullptr");
    return item->next_item;
}

ListItem *list_item_prev(ListItem *item)
{
    if (!item) throw std::invalid_argument("The item pointer is nullptr");
    return item->previous_item;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *ptr = new ListItem;
    if (!list) throw std::invalid_argument("The list pointer is nullptr");

    ptr->previous_item = nullptr;
    ptr->next_item = list->first;
    ptr->value = data;

    if (list->first) {
        list->first->previous_item = ptr;
    }

    list->first = ptr;

    return ptr;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *ptr = new ListItem;

    if (!list) throw std::invalid_argument("The list pointer is nullptr");
    if (!item) throw std::invalid_argument("The item pointer is nullptr");

    ptr->previous_item = item;
    ptr->next_item = item->next_item;
    ptr->value = data;

    if (item->next_item) 
        item->next_item->previous_item = ptr;
    item->next_item = ptr;

    return ptr;
}

ListItem *list_erase_first(List *list)
{
    ListItem *temp_ptr;
    if (!list) throw std::invalid_argument("The list pointer is nullptr");
    if (!(list->first)) throw std::invalid_argument("The list is empty");

    temp_ptr = list->first->next_item;
    if (temp_ptr) temp_ptr->previous_item = nullptr;
    delete list->first;
    list->first = temp_ptr;

    return list->first;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem *temp_ptr;

    if (!list) throw std::invalid_argument("The list pointer is nullptr");
    if (!item) throw std::invalid_argument("The item pointer is nullptr");
    if (!(item->next_item)) throw std::invalid_argument("The item doesn't have a next item");

    temp_ptr = item->next_item->next_item;
    if (temp_ptr) temp_ptr->previous_item = item;
    delete item->next_item;
    item->next_item = temp_ptr;
    
    return temp_ptr;
}
