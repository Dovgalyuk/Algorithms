#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
};

struct List
{
    ListItem *first;
    ListItem *last;
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
    // TODO: free items
    ListItem *item = list->first;
    while (item != NULL) {
        ListItem *first = item->next;
        delete item;
        item = first;
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
    (void)item;
    return NULL;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *item = new ListItem;
    item->data = data;
    item->next = list->first;
    list->first = item;
    if (list->last == NULL) {
        list->last = item;
    }
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == NULL) { // if the item is not specified, insert at the beginning of the list
        return list_insert(list, data);
    }

    ListItem *new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    item->next = new_item;
    if (list->last == item) {
        list->last = new_item;
    }
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, NULL);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem *to_delete = (item == NULL) ? list->first : item->next;

    if (to_delete == NULL) { //if the item to delete is next to the last item, return NULL
        return NULL;
    }

    ListItem *next = to_delete->next;
    if (item == NULL) {
        list->first = next;
    } else {
        item->next = next;
    }

    if (list->last == to_delete) { //if the item to delete is last in the list, last == item
        list->last = item;
    }

    delete to_delete;
    return next;
}
