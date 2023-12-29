#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next = nullptr;
};

struct List
{
    ListItem* head = nullptr;
    ListItem* tail = nullptr;
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    ListItem* current = list->head;
    while (current != nullptr) {
        ListItem* next = current->next;
        delete current;
        current = next;
    }
    // TODO: free items
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

// ListItem *list_item_prev(ListItem *item)
// {
//     return item->prev;
// }

ListItem *list_insert(List *list, Data data)
{
    ListItem* item = new ListItem;
    item->data = data;
    item->next = list->head;
    list->head = item;
    if (list->tail == nullptr) list->tail = item;
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
     if (item == nullptr)
        return nullptr;

    ListItem* NewItem = new ListItem;
   
    NewItem->data = data;
    NewItem->next = item->next;
    item->next = NewItem;

    if (list->tail == item) list->tail = NewItem;

    return NewItem;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == nullptr)
        return nullptr;

    ListItem* item = list->head;
    list->head = item->next;
    if (list->tail == item)
        list->tail = nullptr;

    delete item;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
     if (item == nullptr || item->next == nullptr)
        return nullptr;

    ListItem* to_remove = item->next;
    item->next = to_remove->next;

    if (to_remove->next == nullptr)
        list->tail = item;

    delete to_remove;
    return item->next;
}
