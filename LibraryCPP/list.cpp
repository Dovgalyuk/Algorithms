#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
};

struct List
{
    ListItem *head;
};


List *list_create()
{
    List *list = new List;

    if (list)
        list -> head = nullptr;

    return list;
}

void list_delete(List *list)
{
    if (!list) return;

    // TODO: free items
    ListItem *current = list -> head;

    while (current) {
        ListItem *next = current -> next;
        delete current;
        current = next;
    }

    delete list;
}

ListItem *list_first(List *list)
{
    if (list) 
        return list -> head;

    return nullptr;
}

Data list_item_data(const ListItem *item)
{
    if (item)
        return item -> data;

    return (Data)0;
}

ListItem *list_item_next(ListItem *item)
{
    if (item)
        return item -> next;

    return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    return list_insert_after(list, nullptr, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *new_item = new ListItem;
    new_item -> data = data;

    if (item == nullptr) {
        new_item -> next = list -> head;
        list -> head = new_item;
    }
    else {
        new_item -> next = item -> next;
        item -> next = new_item;
    }

    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list -> head == nullptr)
        return nullptr;

    ListItem *first = list -> head;
    list -> head = first -> next;

    delete first;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr)
        return list_erase_first(list);
    
    ListItem *to_delete = item -> next;

    if (to_delete == nullptr)
        return nullptr;

    item -> next = to_delete -> next;

    delete to_delete;
    return item -> next;
}
