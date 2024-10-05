#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* sled = nullptr;
    ListItem* pred = nullptr;

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

ListItem *list_item_prev(ListItem *item)
{
    if (item != nullptr && item->pred != nullptr) return item->pred;
    else return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* l = new ListItem;
    l->data = data;
    l->pred = nullptr;

    if (list->elem != nullptr) {
        l->sled = list->elem;
        list->elem->pred = l;
    }
    else
        l->sled = nullptr;

    list->elem = l;

    return l;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (list != nullptr && item != nullptr)
    {
        ListItem* l = new ListItem;

        l->pred = item;
        l->sled = item->sled;
        l->data = data;
        if (item->sled != nullptr)
            item->sled->pred = l;
        item->sled = l;

        return l;
    }
    return nullptr;
}

ListItem* list_erase_first(List* list)
{
    if (list != nullptr && list->elem != nullptr)
    {
        ListItem* udal = list->elem;  
        list->elem = udal->sled;      

        if (list->elem != nullptr)
        {
            list->elem->pred = nullptr;   
        }
        delete udal;  

        return list->elem;  
    }
    return nullptr;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (list != nullptr && item != nullptr && item->sled != nullptr)
    {
        ListItem* udal = item->sled;
        item->sled = udal->sled;  

        if (item->sled != nullptr)
        {
            item->sled->pred = item;  
        }

        delete udal;  
        return item->sled;  
    }
    return nullptr;
}
