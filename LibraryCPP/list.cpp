#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* sled = nullptr;
};

struct List
{
    ListItem* elem = nullptr;
};

List *list_create()
{
    List* L = new List;
    return L;
}

void list_delete(List *list)
{
    // TODO: free items
    if (list != nullptr)
    {
        ListItem* tek = list->elem;
        while (tek != nullptr)
        {
            ListItem* sl = tek->sled;
            delete tek;
            tek = sl;
        }
        delete list;
    }
}

ListItem *list_first(List *list)
{
    if (list != nullptr)
        return list->elem;
    else return nullptr;
}

Data list_item_data(const ListItem *item)
{
    if (item != nullptr)
        return item->data;
    return (Data)0;
}

ListItem *list_item_next(ListItem *item)
{
    if (item != nullptr && item->sled != nullptr) return item->sled;
    return nullptr;
}

ListItem *list_insert(List* list, Data data)
{
    ListItem* l = new ListItem;
    l->data = data;


    l->sled = list->elem;
    list->elem = l;

    return l;
}

ListItem *list_insert_after(List* list, ListItem* item, Data data)
{
    if (list != nullptr && item != nullptr)
    {
        ListItem* l = new ListItem;
        l->data = data;
        l->sled = item->sled;
        item->sled = l;

        return l;
    }
    return nullptr;
}

ListItem *list_erase_first(List* list)
{
    if (list != nullptr && list->elem != nullptr)
    {
        ListItem* udal = list->elem;
        list->elem = udal->sled;  

        delete udal;  

        return list->elem;  
    }
    return nullptr;
}

ListItem *list_erase_next(List* list, ListItem* item)
{
    if (list != nullptr && item != nullptr && item->sled != nullptr)
    {
        ListItem* udal = item->sled;
        item->sled = udal->sled;  

        delete udal; 

        return item->sled;  
    }
    return nullptr;
}
