#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
    ListItem *prev;
};

struct List
{
    ListItem *head;
};

List *list_create()
{
    return new List{nullptr};
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

ListItem *list_item_prev(ListItem *item)
{
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *newListItem = new ListItem{data, list->head, nullptr};

    if (list->head)
    {
        list->head->prev = newListItem;
    }
    else
    {
        list->head = newListItem;
    }
    list->head = newListItem;
    return newListItem;
}

ListItem *list_insert_after(ListItem *item, Data data)
{
    ListItem *newListItem = new ListItem{data};

    newListItem->next = item->next;
    ;
    newListItem->prev = item;

    if (item->next) {
        item->next->prev = newListItem;
    }
    item->next = newListItem;

    return newListItem;
}

ListItem *list_erase_first(List *list)
{
    if (list->head)
    {
        ListItem *temp = list->head;

        if (list->head->next)
        {
            list->head->next->prev = list->head->prev;
        }

        list->head = list->head->next;

        delete temp;
        return list->head;
    }
    return nullptr;
}

ListItem *list_erase_next(ListItem *item)
{
    if (!item)
    {
        return nullptr;
    }

    ListItem *deletedItem = item->next;
    item->next = deletedItem->next;

    if (item->next)
    {
        item->next->prev = item;
    }

    if (item->next == item)
    {
        item->next = nullptr;
    }

    delete deletedItem;
    return item->next;
}