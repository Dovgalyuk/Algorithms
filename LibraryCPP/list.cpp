#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* pointer_to_next_element;
    ListItem* pointer_to_previous_element;
};

struct List
{
    ListItem* pointer_to_head_list;
    ListItem* pointer_to_tail_list;
};

List* list_create()
{
    List* list_new = new List;

    list_new->pointer_to_head_list = nullptr;
    list_new->pointer_to_tail_list = nullptr;

    return list_new;
}

void list_delete(List* list)
{
    ListItem* current_pointer = list->pointer_to_head_list;

    while (current_pointer != nullptr)
    {
        ListItem* next_pointer = current_pointer->pointer_to_next_element;
        delete current_pointer;
        current_pointer = next_pointer;
    }
    delete list;
}

ListItem* list_first(List* list)
{
    return list->pointer_to_head_list;
}

Data list_item_data(const ListItem* item)
{
    return item->data;
}

ListItem* list_item_next(ListItem* item)
{
    return item->pointer_to_next_element;
}

ListItem* list_item_prev(ListItem* item)
{
    return item->pointer_to_previous_element;
}

ListItem* list_insert(List* list, Data data)
{
    ListItem* item_new = new ListItem{ data, nullptr, nullptr };

    if (list->pointer_to_head_list == nullptr)
    {
        list->pointer_to_head_list = item_new;
        list->pointer_to_tail_list = item_new;
    }
    else
    {
        item_new->pointer_to_next_element = list->pointer_to_head_list;
        list->pointer_to_head_list->pointer_to_previous_element = item_new;
        list->pointer_to_head_list = item_new;
    }

    return item_new;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (item == nullptr)
    {
        return nullptr;
    }

    ListItem* item_new = new ListItem{ data, nullptr, nullptr };

    if (item_new == nullptr)
    {
        return nullptr;
    }

    item_new->pointer_to_next_element = item->pointer_to_next_element;
    item_new->pointer_to_previous_element = item;

    if (item_new->pointer_to_next_element != nullptr)
    {
        item->pointer_to_next_element->pointer_to_previous_element = item_new;
    }
    else
    {
        list->pointer_to_tail_list = item_new;
    }

    item->pointer_to_next_element = item_new;

    return item_new;
}

ListItem* list_erase_first(List* list)
{

    if (list->pointer_to_head_list == nullptr)
    {
        return nullptr;
    }

    ListItem* item_new = list->pointer_to_head_list;
    list->pointer_to_head_list = item_new->pointer_to_next_element;
    
    if (list->pointer_to_head_list != nullptr)
    {
        list->pointer_to_head_list->pointer_to_previous_element = nullptr;
    }
    else
    {
        list->pointer_to_tail_list = nullptr;
    }

    delete item_new;

    return list->pointer_to_head_list;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    
    if (item == nullptr || item->pointer_to_next_element == nullptr)
    {
        return nullptr;
    }

    ListItem* to_delete = item->pointer_to_next_element;
    item->pointer_to_next_element = to_delete->pointer_to_next_element;

    if (to_delete->pointer_to_next_element != nullptr)
    {
        to_delete->pointer_to_next_element->pointer_to_previous_element = item;
    }
    else
    {
        list->pointer_to_tail_list = item;
    }

    delete to_delete;
    return item->pointer_to_next_element;
}