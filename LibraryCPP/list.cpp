#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
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
    ListItem* current = list->first;
    while (current != NULL)
    {
        ListItem* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

ListItem* list_first(List* list)
{
    return list->first;
}

Data list_item_data(const ListItem* item)
{
    return item->data;
}

ListItem* list_item_next(ListItem* item)
{
    return item->next;
}


ListItem* list_insert(List* list, Data data)
{
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = list->first;
    list->first = newItem;
    return newItem;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (item == NULL)
    {
        return list_insert(list, data);
    }
    else
    {
        ListItem* newItem = new ListItem;
        newItem->data = data;
        newItem->next = item->next;
        item->next = newItem;
        return newItem;
    }
}

ListItem* list_erase_first(List* list)
{
    if (list->first == NULL)
    {
        return NULL;
    }
    else
    {
        ListItem* removedItem = list->first;
        list->first = list->first->next;
        delete removedItem;
        return list->first;
    }
}

ListItem* list_erase_next(ListItem* item)
{
    if (item == NULL || item->next == NULL)
    {
        return NULL;
    }
    else
    {
        ListItem* removedItem = item->next;
        item->next = item->next->next;
        delete removedItem;
        return item->next;
    }
}