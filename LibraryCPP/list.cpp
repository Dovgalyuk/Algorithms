#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
};

struct List
{
    ListItem *head;
    List() : head(nullptr) {}
};

List *list_create()
{
    return new List();
}

void list_delete(List *list)
{
    while (list->head)
    {
        ListItem *temp = list->head->next;
        delete list->head;
        list->head = temp;
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
    return NULL;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *item = new ListItem{data, list->head};
    list->head = item;
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *new_item = new ListItem{data, item->next};
    item->next = new_item;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (!list->head)
        return nullptr;
    ListItem *next_item = list->head->next;
    delete list->head;
    list->head = next_item;
    return next_item;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!item || !item->next)
        return nullptr;
    ListItem *to_delete = item->next;
    item->next = item->next->next;
    delete to_delete;
    return item->next;
}
