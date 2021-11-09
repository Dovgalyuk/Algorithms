#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
};

struct List
{
    ListItem* head;
};

List *list_create()
{
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List *list)
{
    while (list->head != nullptr)
    {
        ListItem* prev = list->head;
        list->head = list_item_next(prev);
        delete prev;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list->head;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

//ListItem *list_item_prev(ListItem *item)
//{
//    return NULL;
//}

ListItem *list_insert(List *list, Data data)
{
    ListItem* item = new ListItem;
    item->data = data;
    item->next = list->head;
    list->head = item;

    return nullptr;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    item->next = new_item;

    return nullptr;
}

//ListItem *list_erase(List *list, ListItem *item)
//{
//    return NULL;
//}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem* delet = item->next;
    item->next = delet->next;
    delete delet;

    return nullptr;
}

void list_erase_head(List* list)
{
    ListItem* head = list->head;
    list->head = list_item_next(list->head);
    delete head;
}