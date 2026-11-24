#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
    ListItem *prev;
    bool head;
};

struct List
{
    ListItem *head;
};

static ListItem *real_item(ListItem *item)
{
    return item->head ? NULL : item;
}

List *list_create()
{
    List *list = new List;
    list->head = new ListItem;
    list->head->data = Data();
    list->head->next = list->head;
    list->head->prev = list->head;
    list->head->head = true;
    return list;
}

void list_delete(List *list)
{
    while (list_first(list))
        list_erase_first(list);
    delete list->head;
    delete list;
}

ListItem *list_first(List *list)
{
    return real_item(list->head->next);
}

ListItem *list_last(List *list)
{
    return real_item(list->head->prev);
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return real_item(item->next);
}

ListItem *list_item_prev(ListItem *item)
{
    return real_item(item->prev);
}

ListItem *list_insert(List *list, Data data)
{
    return list_insert_after(list, NULL, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *prev = item ? item : list->head;
    ListItem *added = new ListItem;
    added->data = data;
    added->head = false;
    added->prev = prev;
    added->next = prev->next;
    prev->next->prev = added;
    prev->next = added;
    return added;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, NULL);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem *prev = item ? item : list->head;
    ListItem *erased = prev->next;
    if (erased->head)
        return NULL;
    prev->next = erased->next;
    erased->next->prev = prev;
    delete erased;
    return real_item(prev->next);
}
