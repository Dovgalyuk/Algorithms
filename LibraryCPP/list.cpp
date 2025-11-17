#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
};

struct List
{
    ListItem* first;
};

List *list_create()
{
    List* list = new List;
    list->first = nullptr;
    return list;
}

void list_delete(List* list)
{
    ListItem* curr = list->first;
    while (curr != nullptr)
    {
        ListItem* next = curr->next;
        delete curr;
        curr = next;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list->first;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if (item == nullptr)
        return nullptr;
    return item->next;
}

ListItem *list_item_prev(List* list, ListItem *item)
{
    if (list->first == nullptr || list->first == item)
        return nullptr; 

    ListItem* current = list->first;
    while (current != nullptr && current->next != item)
    {
        current = current->next;
    }
    return current; 
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* new_item = new ListItem;    
    new_item->data = data;                 
    new_item->next = list->first;         
    list->first = new_item;                
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == nullptr)
        return list_insert(list, data);   

    ListItem* new_item = new ListItem;   
    new_item->data = data;
    new_item->next = item->next;           
    item->next = new_item;                 
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list->first == nullptr)
        return nullptr;

    ListItem* rm = list->first;
    list->first = rm->next;
    delete rm;
    return list->first;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr || item->next == nullptr)
        return nullptr;                   

    ListItem* rm = item->next;      
    item->next = rm->next;           
    delete rm;                        
    return item->next;
}
