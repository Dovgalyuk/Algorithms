#include "list.h"
#include <cstddef>
#include <string>

struct ListItem
{
    Data data;
    ListItem* next;
};

struct List
{
    ListItem* head;
};

List* list_create()
{
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List* list)
{
    while (list->head != nullptr)
    {
        ListItem* temp = list->head;
        list->head = list->head->next;
        delete temp;
    }
    delete list;
}

ListItem* list_first(List* list)
{
    return list->head;
}

Data list_item_data(const ListItem* item)
{
    return item->data;
}

ListItem* list_item_next(ListItem* item)
{
    return item ? item->next : nullptr;
}

ListItem* list_item_prev(ListItem* item)
{
    return nullptr;
}

ListItem* list_insert(List* list, Data data)
{
    ListItem* item = new ListItem;
    item->data = data;
    item->next = list->head;
    list->head = item;
    return item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (!item)
        return list_insert(list, data);

    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    item->next = new_item;
    return new_item;
}

ListItem* list_erase_first(List* list)
{
    if (!list->head) return nullptr;
    ListItem* temp = list->head;
    list->head = list->head->next;
    delete temp;
    return list->head;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (!item || !item->next) return nullptr;
    ListItem* temp = item->next;
    item->next = temp->next;
    delete temp;
    return item->next;
}