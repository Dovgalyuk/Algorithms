/*#include <cstddef>
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
}*/


#include <cstddef>
#include "list.h"

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

struct ListItem
{
};

struct List
{
};

List* list_create()
{
    return new List;
}

void list_delete(List* list)
{
    // TODO: free items
    delete list;
}

ListItem* list_first(List* list)
{
    UNUSED(list);
    return NULL;
}

Data list_item_data(const ListItem* item)
{
    UNUSED(item);
    return (Data)0;
}

ListItem* list_item_next(ListItem* item)
{
    UNUSED(item);
    return NULL;
}

ListItem* list_item_prev(ListItem* item)
{
    UNUSED(item);
    return NULL;
}

ListItem* list_insert(List* list, Data data)
{
    UNUSED(list);
    UNUSED(data);
    return NULL;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    UNUSED(list);
    UNUSED(item);
    UNUSED(data);
    return NULL;
}

ListItem* list_erase_first(List* list)
{
    UNUSED(list);
    return NULL;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    UNUSED(list);
    UNUSED(item);
    return NULL;
}