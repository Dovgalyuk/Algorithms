#include <stdlib.h>
#include "list.h"

typedef struct ListItem
{
} ListItem;

typedef struct List
{
} List;

List *list_create(FFree f)
{
    return malloc(sizeof(List));
}

void list_delete(List *list)
{
    // TODO: free items
    free(list);
}

ListItem *list_first(List *list)
{
    return NULL;
}

Data list_item_data(const ListItem *item)
{
    return (Data)0;
}

ListItem *list_item_next(ListItem *item)
{
    return NULL;
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
