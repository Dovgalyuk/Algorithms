#include <cstddef>
#include "list.h"

struct ListItem
{
    Data value;
    ListItem* next;
    ListItem* prev;
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
    if(list->head != nullptr) 
    {
        ListItem* current = list->head;
        ListItem* last = list->head->prev;
        
        last->next = nullptr;
        
        while (current != nullptr) {
            ListItem* next = current->next;
            delete current;
            current = next;
        }
    }

    delete list;
}

ListItem *list_first(List *list)
{
    return list->head;
}

Data list_item_data(const ListItem *item)
{
    return item->value;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->value = data;

    if(list->head == nullptr)
    {
        new_item->next = new_item;
        new_item->prev = new_item;
        list->head = new_item;
    }
    else
    {
        ListItem* first = list->head;
        ListItem* last = list->head->prev;

        new_item->next = first;
        new_item->prev = last;

        first->prev = new_item;
        last->next = new_item;

        list->head = new_item;
    }

    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if(item == nullptr)
    {
        return list_insert(list, data);
    }

    ListItem* new_item = new ListItem;
    new_item->value = data;
   
    ListItem* next = item->next;

    new_item->next = next;
    new_item->prev = item;

    next->prev = new_item;
    item->next = new_item;

    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if(list->head == nullptr)
    {
        return nullptr;
    }

    ListItem* next = list->head->next;
    ListItem* prev = list->head->prev;
    ListItem* del = list->head;

    if(next == del)
    {
        list->head = nullptr;
    }
    else
    {
        list->head = next;
        next->prev = prev;
        prev->next = next;
    }

    delete del;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if(item == nullptr)
    {
        return list_erase_first(list);
    }

    ListItem* del = item->next;
    ListItem* next = del->next;

    item->next = next;
    next->prev = item;

    if(del == list->head)
    {
        list->head = next;
    }

    delete del;
    return next;
}
