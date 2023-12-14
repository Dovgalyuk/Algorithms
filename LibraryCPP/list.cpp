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
    list->head->prev = newListItem;
    list->head = newListItem;
    return newListItem;
}

ListItem *list_insert_after(ListItem *item, Data data)
{
    if (!item)
    {
        return nullptr;
    }

    ListItem *newListItem = new ListItem{data, item->next, item};

    item->next = newListItem;

    if (newListItem->next)
    {
        newListItem->next->prev = newListItem;
    }

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
    if (!item || !item->next)
    {
        return nullptr;
    }

    ListItem *deletedItem = item->next;
    item->next = deletedItem->next;

    if (item->next)
    {
        item->next->prev = item;
    }

    delete deletedItem;
    return item->next;
}