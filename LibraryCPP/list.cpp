#include <cstddef>
#include "list.h"

struct ListItem
{
    int data;
    ListItem* next;
};

struct List
{
    ListItem* last = NULL;
    ListItem* first = NULL:
};

void insertMake(List* list, Data data)
{
    ListItem* l = new listItem;
    l->data = data;
    if (list->first == NULL) {
        list->last = l;
        list->first = l;
    }
    else {
        list->last->next = l;
        list->last = l;
    }
}

void list_delete(List *list)
{
    while (list->last != nullptr) {
        list->first = nullptr;
        list->first->next = list->first;
    }
}

ListItem *list_first(List *list)
{
    return list->first;
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
    return NULL;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    return NULL;
}

ListItem *list_erase_first(List *list)
{
    return NULL;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    return NULL;
}
