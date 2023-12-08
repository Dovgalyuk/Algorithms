#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next = nullptr;
};

struct List
{
    ListItem *head = nullptr;
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    while (list->head)
    {
        list_erase_first(list);
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list->head;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *newListItem = new ListItem;
    newListItem->data = data;
    newListItem->next = list->head;

    list->head = newListItem;
    return newListItem;
}

ListItem *list_insert_after(ListItem *item, Data data)
{
    if (!item)
    {
        return nullptr;
    }

    ListItem *newListItem = new ListItem;
    newListItem->data = data;
    newListItem->next = item->next;
    item->next = newListItem;

    return newListItem;
}

ListItem *list_erase_first(List *list)
{
    if (list->head)
    {
        ListItem *temp = list->head;
        list->head = list->head->next;
        delete temp;
        return list->head;
    }
    return nullptr;
}

ListItem *list_erase_next(ListItem *item)
{
    if (!item || !item->next)
    {
        return nullptr;
    }

    ListItem *deletedItem = item->next;
    item->next = deletedItem->next;

    delete deletedItem;
    return item->next;
}