#include <cstddef>
#include "list.h"

struct ListItem
{
    Data* data;
    ListItem* next;
};

struct List
{
    ListItem* last = NULL;
    ListItem* first = NULL;
};

list* listCreate() {
    List* list = new List;
    list->last = NULL;
    trturn list;
}
void insertMake(List* list, Data data)
{
    ListItem* l = new listItem;
    l->data = data;
    if (list->last == NULL) {
        list->last = l;
    }
    else {
        list->last->next = l;
        list->last = l;
    }
}

void list_delete(List *list)
{
    delete list;
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

ListItem *list_erase_last(List *list)
{
    while(list->first->next != list->last) {
        list->first == list->first->next;
    }
    ListItem* item == nullptr;
    item = list->last;
    list->last == list->first;
    return item;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    return NULL;
}
