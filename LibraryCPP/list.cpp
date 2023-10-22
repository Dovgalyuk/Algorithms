#include <cstddef>
#include "list.h"

struct ListItem
{
    Data field;
    ListItem* next;
};

struct List
{
    ListItem* Head;
};

List *list_create()
{
    List* list = new List;
    list->Head = nullptr;
    return list;
}

void list_delete(List *list)
{
    ListItem* p = list->Head;
    while (p != nullptr)
    {
        ListItem* next = p->next;
        delete p;
        p = next;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list->Head;
}

Data list_item_data(const ListItem *item)
{
    return item->field;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

//ListItem *list_item_prev(ListItem *item) // забил
//{
//    return nullptr;
//}

ListItem *list_insert(List *list, Data data)
{
    ListItem* new_Head = new ListItem{ data, nullptr };

    if (list->Head == nullptr)
    {
        list->Head = new_Head;
    }
    else
    {
        new_Head->next = list->Head;
        list->Head = new_Head;
    }

    return new_Head;
}

ListItem *list_insert_after(List* list, ListItem* item, Data data)
{
    if (item == nullptr || list==nullptr) return nullptr;

    ListItem *new_item = new ListItem{ data, nullptr };

    if (new_item == nullptr)
        return nullptr;

    new_item->next = item->next;
    item->next = new_item;

    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list->Head == nullptr)
        return nullptr;

    ListItem* p = list->Head;
    list->Head = p->next;

    delete p;
    return list->Head;
}

ListItem *list_erase_next(List* list, ListItem* item)
{
    if (item == nullptr || item->next == nullptr || list==nullptr)
        return nullptr;

    ListItem* p;
    p = item->next;
    item->next = p->next;

    delete p;
    return item->next; //maybe return nullptr
}
