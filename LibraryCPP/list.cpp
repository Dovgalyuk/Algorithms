#include <cstddef>
#include "list.h"

struct ListItem
{
    ListItem* pNext;
    Data data;

};

struct List
{
    ListItem* head;
};

List* list_create()
{
    List* list = new list;
    list->head = nullptr;
    return list;
}

void list_delete(List* list)
{
    // TODO: free items
    while (list_item_next(list->head) != nullptr)
    {
        list_erase_next(list, list->head);
    }
    delete list->head;
    delete list;
    
}

ListItem* list_first(List* list)
{
    return list->head;
}

Data list_item_data(const ListItem* item)
{
    return item->data;
}

ListItem* list_item_next(ListItem* item)
{
    return item->pNext;
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
    a->pNext= list_first(list);
    list->head = a;
    return a;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    ListItem* a = new ListItem;
    a->data = data;
    a->pNext = item->pNext;
    item->pNext = a;
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
    if (list->head)
    {
        erase = item->pNext;
        item->pNext = list_item_next(list_item_next(item));
        delete erase;
        return item;
    }
    else
        return NULL;
}
