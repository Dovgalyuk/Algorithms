#include <stdlib.h>
#include "list.h"

struct ListItem
{
};

struct List
{
};

List *list_create()
{
    return NULL;
}

void list_delete(List *list)
{
}

ListItem *list_first(List *list)
{
    return NULL;
}

int list_item_data(ListItem *item)
{
    return 0;
}

ListItem *list_item_next(ListItem *item)
{
    return NULL;
}

ListItem *list_item_prev(ListItem *item)
{
    return NULL;
}

ListItem *list_insert(List *list, int data)
{
    return NULL;
}

ListItem *list_insert_after(List *list, ListItem *item, int data)
{
    return NULL;
}

ListItem *list_erase(List *list, ListItem *item)
{
    return NULL;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    return NULL;
}
