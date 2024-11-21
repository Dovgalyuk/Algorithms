#include <cstddef>
#include "list.h"

struct ListItem
{
};

struct List
{
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    // TODO: free items
    delete list;
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
