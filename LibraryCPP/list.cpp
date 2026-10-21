#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;      // значение элемента
    ListItem *next; // указатель на следующий элемент,NULL если его нету
    ListItem *prev; //указатель на предыдущий элемент,NULL если его нету
};

struct List
{
    ListItem *first; // указатель на первый
    ListItem *last;  // указатель на последний
};

List *list_create()
{
    List *list = new List;
    list->first = NULL;
    list->last = NULL;
    return list;
}

void list_delete(List *list)
{

    ListItem *item = list->first;
    while (item != NULL)
    {
        ListItem *next = item->next;
        delete item;
        item = next;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list->first;
}

ListItem *list_last(List *list)
{
    return list->last;
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
    ListItem *new_item = new ListItem;
    new_item->data = data;
    new_item->prev = NULL;

    new_item->next = list->first;
    if (list->first != NULL)
    {
        list->first->prev = new_item;
    }
    else
    {
        list->last = new_item;
    }
    list->first = new_item;

    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == NULL)
    {
        return list_insert(list, data);
    }

    ListItem *new_item = new ListItem;
    new_item->data = data;
    new_item->prev = item;
    new_item->next = item->next;

    if (item->next != NULL)
    {
        item->next->prev = new_item;
    }
    else
    {
        list->last = new_item;
    }
    item->next = new_item;

    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list->first == NULL)
    {
        return NULL;
    }

    ListItem *old_first = list->first;
    list->first = old_first->next;

    if (list->first != NULL)
    {
        list->first->prev = NULL;
    }
    else
    {
        list->last = NULL;
    }

    delete old_first;
    return list->first;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == NULL)
    {
        return list_erase_first(list);
    }

    ListItem *to_delete = item->next;
    if (to_delete == NULL)
    {
        return NULL;
    }

    item->next = to_delete->next;
    if (to_delete->next != NULL)
    {
        to_delete->next->prev = item;
    }
    else
    {
        list->last = item;
    }

    delete to_delete;
    return item->next;
}
