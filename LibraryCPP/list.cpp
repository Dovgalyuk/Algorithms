#include <cstddef>
#include "list.h"

struct ListItem
{
    Data value;
    ListItem* next = nullptr;
    ListItem* prev = nullptr;
};

struct List
{
    ListItem* node = nullptr;
};

List *list_create()
{
    List* newList = new List;
    return newList;
}

void list_delete(List* list)
{
    if (list != nullptr)
    {
        ListItem* current = list->node;
        while (current != nullptr)
        {
            ListItem* next = current->next;
            delete current;
            current = next;
        }
        delete list;
    }
}


ListItem *list_first(List *list)
{
    if (list != nullptr)
        return list->node;
    return nullptr;
}

Data list_item_data(const ListItem *item)
{
    if (item != nullptr)
        return item->value;
    return (Data)0;
}

ListItem *list_item_next(ListItem *item)
{
    if(item != nullptr && item->next != nullptr)
        return item->next;
    return nullptr;
}

ListItem *list_item_prev(ListItem *item)
{
    if (item != nullptr && item->prev != nullptr)
        return item->prev;
    return nullptr;
}

ListItem* list_insert(List* list, Data data)
{
    ListItem* newEl = new ListItem;
    newEl->value = data;
    newEl->prev = nullptr;

    if (list->node != nullptr)
        newEl->next = list->node;
    else
        newEl->next = nullptr;

    list->node = newEl;

    return newEl;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (list != nullptr && item != nullptr)
    {
        ListItem* newEl = new ListItem;
        newEl->value = data;
        newEl->prev = item;

        if(item->next != nullptr)
            newEl->next = item->next;

        item->next = newEl;

        return newEl;
    }

    return nullptr;
}

ListItem *list_erase_first(List *list)
{
    if (list != nullptr && list->node != nullptr)
    {
        ListItem* temp = list->node->next;
        if(temp != nullptr)
            temp->prev = nullptr;
        delete list->node;
        list->node = temp;

        return list->node;
    }
    return NULL;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (list != nullptr && item != nullptr && item->next != nullptr)
    {
        item->next->next->prev = item;
        ListItem* temp = item->next->next;
        delete item->next;
        item->next = temp;
        return temp;
    }

    return nullptr;
}
