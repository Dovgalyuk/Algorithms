#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;

    ListItem(Data d) : data(d), next(nullptr) {}
};

struct List
{
    ListItem* head;

    List() : head(nullptr) {}
};

List* list_create()
{
    return new List;
}

void list_delete(List* list)
{
    ListItem* current = list->head;
    while (current)
    {
        ListItem* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

ListItem* list_first(List* list)
{
    return list->head;
}

Data list_item_data(const ListItem* item)
{
    return item ? item->data : (Data)0;
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
    ListItem* new_item = new ListItem(data);
    new_item->next = list->head;
    list->head = new_item;
    return new_item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (!item)
        return nullptr;

    ListItem* new_item = new ListItem(data);
    new_item->next = item->next;
    item->next = new_item;
    return new_item;
}

ListItem* list_erase_first(List* list)
{
    if (!list->head)
        return nullptr;

    ListItem* removed_item = list->head;
    list->head = list->head->next;
    delete removed_item;
    return list->head;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (!item || !item->next)
        return nullptr;

    ListItem* removed_item = item->next;
    item->next = item->next->next;
    delete removed_item;
    return item->next;
}