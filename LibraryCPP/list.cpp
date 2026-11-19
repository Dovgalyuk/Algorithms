#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
    ListItem *prev;
    bool is_dummy;
};

struct List
{
    ListItem *dummy;
};

List *list_create()
{
    List *list = new List;
    list->dummy = new ListItem;
    list->dummy->data = (Data)0;
    list->dummy->next = list->dummy;
    list->dummy->prev = list->dummy;
    list->dummy->is_dummy = true;
    return list;
}

void list_delete(List *list)
{
    if (!list)
    {
        return;
    }

    ListItem *curr = list->dummy->next;
    while (curr != list->dummy)
    {
        ListItem *next = curr->next;
        delete curr;
        curr = next;
    }

    delete list->dummy;
    delete list;
}

ListItem *list_first(List *list)
{
    if (!list || list->dummy->next == list->dummy)
    {
        return NULL;
    }
    return list->dummy->next;
}

ListItem *list_last(List *list)
{
    if (!list || list->dummy->prev == list->dummy)
    {
        return NULL;
    }
    return list->dummy->prev;
}

Data list_item_data(const ListItem *item)
{
    if (!item)
    {
        return (Data)0;
    }
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if (!item || !item->next || item->next->is_dummy)
    {
        return NULL;
    }
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    if (!item || !item->prev || item->prev->is_dummy)
    {
        return NULL;
    }
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    if (!list)
    {
        return NULL;
    }
    return list_insert_after(list, list->dummy, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list)
    {
        return NULL;
    }

    ListItem *target = item;
    if (target == NULL)
    {
        target = list->dummy;
    }

    ListItem *new_item = new ListItem;
    new_item->data = data;
    new_item->is_dummy = false;
    new_item->next = target->next;
    new_item->prev = target;

    target->next->prev = new_item;
    target->next = new_item;

    return new_item;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, NULL);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list)
    {
        return NULL;
    }

    ListItem *target = item;
    if (target == NULL)
    {
        target = list->dummy;
    }

    ListItem *to_delete = target->next;
    if (to_delete == list->dummy)
    {
        return NULL;
    }

    ListItem *after = to_delete->next;
    target->next = after;
    after->prev = target;

    delete to_delete;

    if (after->is_dummy)
    {
        return NULL;
    }
    return after;
}
