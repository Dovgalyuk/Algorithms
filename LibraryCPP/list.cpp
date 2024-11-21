#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;

    ListItem *pointer_to_previous;
    ListItem *pointer_to_next;
};

struct List
{
    ListItem *head_of_list;
    ListItem *tail_of_list;
};

List *list_create()
{
    List *new_list = new List;
    new_list->head_of_list = nullptr;
    new_list->tail_of_list = nullptr;

    return new_list;
}

void list_delete(List *list)
{
    ListItem *current_list_item = list->head_of_list;

    while (current_list_item != nullptr)
    {
        ListItem *next_pointer = current_list_item->pointer_to_next;
        delete current_list_item;
        current_list_item = next_pointer;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list->head_of_list;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item->pointer_to_next;
}

ListItem *list_item_prev(ListItem *item)
{
    if (item->pointer_to_previous != nullptr)
        return item->pointer_to_previous;
    else
        return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *new_item = new ListItem{data, nullptr, nullptr};

    if (list->head_of_list == nullptr)
    {
        list->head_of_list = new_item;
        list->tail_of_list = new_item;
    }
    else
    {
        new_item->pointer_to_next = list->head_of_list;
        list->head_of_list->pointer_to_previous = new_item;
        list->head_of_list = new_item;
    }

    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item->pointer_to_next == nullptr)
        return list_insert(list, data);
    else
    {
        ListItem *list_item_to_insert = new ListItem{data, item, item->pointer_to_next};
        item->pointer_to_next = list_item_to_insert;
        list_item_to_insert->pointer_to_next->pointer_to_previous = list_item_to_insert;

        return list_item_to_insert;
    }
}

ListItem *list_erase_first(List *list)
{
    if (list->head_of_list == nullptr)
        return nullptr;

    ListItem *item_to_delete = list->head_of_list;
    list->head_of_list = item_to_delete->pointer_to_next;

    if (list->head_of_list != nullptr)
        list->head_of_list->pointer_to_previous = nullptr;
    else
        list->tail_of_list = nullptr;

    delete item_to_delete;

    return list->head_of_list;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr || item->pointer_to_next == nullptr)
        return nullptr;
    else if (item->pointer_to_next->pointer_to_next == nullptr)
    {
        delete item->pointer_to_next;
        list->tail_of_list = item;
        item->pointer_to_next = nullptr;

        return nullptr;
    }
    else
    {
        ListItem *to_delete = item->pointer_to_next;
        item->pointer_to_next = item->pointer_to_next->pointer_to_next;
        item->pointer_to_next->pointer_to_previous = item;

        delete to_delete;

        return item->pointer_to_next;
    }
}
