#include <cstddef>
#include "list.h"

struct ListItem
{
    Data value;
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
    ListItem* cur = list->head;
    while (cur != nullptr)
    {
        ListItem* next = cur->next;
        delete cur;
        cur = next;
    }
    delete list;
}

ListItem* list_first(List* list)
{
    return list->head;
}

Data list_item_data(const ListItem* item)
{
    return item->value;
}

ListItem* list_item_next(ListItem* item)
{
    return item->next;
}

ListItem* list_item_prev(ListItem* item)
{
    
    return NULL;
}


ListItem* list_insert(List* list, Data data)
{
    ListItem* item = new ListItem;
    item->value = data;
    item->next = list->head;

    list->head = item;
    return item;
}


ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (item == NULL)
    {
        return list_insert(list, data);
    }

    ListItem* new_item = new ListItem;
    new_item->value = data;
    new_item->next = item->next;

    item->next = new_item;
    return new_item;
}


ListItem* list_erase_first(List* list)
{
    if (list->head == NULL)
    {
        return NULL;
    }

    ListItem* del = list->head;
    list->head = del->next;
    delete del;

    return list->head;
}


ListItem* list_erase_next(List* list, ListItem* item)
{
    if (item == NULL)
    {
        return list_erase_first(list);
    }

    if (item->next == NULL)
    {
        return NULL;
    }

    ListItem* del = item->next;
    item->next = del->next;
    delete del;

    return item->next;
}
