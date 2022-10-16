#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
};

struct List
{
    ListItem* head;
};

List* list_create()
{
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List* list)
{
    while (list->head != nullptr)
    {
        list_erase(list, list->head);
    }
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
    return item->next;
}

ListItem* list_item_prev(ListItem* item)
{
    return NULL;
}

ListItem* list_insert(List* list, Data data)
{
    ListItem* item = new ListItem;
    item->data = data;
    item->next = list->head;
    list->head = item;
    return item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = item->next;
    item->next = newItem;
    return newItem;
}

ListItem* list_erase(List* list, ListItem* item)
{
    ListItem* currect = list->head;
    ListItem* last = currect;
    while (currect != item)
    {
        last = currect;
        currect = currect->next;
    }
    if (last == currect) {
        list->head = currect->next;
    }
    else {
        last->next = currect->next;
    }
    delete currect;
    return NULL;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    ListItem* newItem = item->next;
    item->next = newItem->next;
    delete newItem;
    return item;
}
