#include <cstddef>
#include "list.h"

struct ListItem
{
    int data;
    ListItem* next;
};

struct List
{
    ListItem* current;
};

List *list_create()
{
    List* list = new List;
    list->current = nullptr;
    return new List;
}

void list_delete(List *list)
{
    while (list->current != nullptr) {
        list->current->next
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return NULL;
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
