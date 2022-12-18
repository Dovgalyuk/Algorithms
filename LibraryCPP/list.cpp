#include <cstddef>
#include "list.h"

struct ListItem
{
    ListItem* next;
    Data data;

};

struct List
{
    ListItem* top;
};

List* list_create()
{
    List* list = new List;
    list->top = nullptr;
    return list;
}

void list_delete(List* list)
{
    // TODO: free items
    while (list_item_next(list->top))
    {
        list_erase_next(list, list->top);
    }
    delete list->top;
    delete list;

}

ListItem* list_first(List* list)
{
    if (list->top)
        return list->top;
    else
        return NULL;

}

Data list_item_data(const ListItem* item)
{
    if (item)
        return item->data;
    else
        return NULL;
}

ListItem* list_item_next(ListItem* item)
{
    if (item)
        return item->next;
    else
        return NULL;
}

// Not applicable for the singly linked lists.
ListItem* list_item_prev(ListItem* item)
{
    return NULL;
}

ListItem* list_insert(List* list, Data data)
{
    ListItem* a = new ListItem;
    a->data = data;
    a->next = list_first(list);
    list->top = a;
    return a;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    ListItem* a = new ListItem;
    a->data = data;
    a->next = item->next;
    item->next = a;
    return a;
}

// Not applicable for the singly linked lists.
ListItem* list_erase(List* list, ListItem* item)
{
    return NULL;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    ListItem* erase = nullptr;
    if (list_item_next(item))
    {
        erase = item->next;
        item->next = list_item_next(list_item_next(item));
        delete erase;
        return item;
    }
    else
        return NULL;
}
