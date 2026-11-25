#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* prev;
    ListItem* next;
};

struct List
{
    ListItem* first;
    ListItem* last;
};

List *list_create()
{
    List* list = new List;
    list->first = nullptr;
    list->last = nullptr;
    return list;
}

void list_delete(List *list)
{
    ListItem* current = list->first;
    while (current!=nullptr){
        ListItem* current1 = current->next;
        delete current;
        current = current1;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list->first;
}

ListItem *list_last(List *list)
{
    return list->last;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
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
    ListItem* old_first = list->first;
    new_item->data = data;
    new_item->next = old_first;
    new_item->prev = nullptr;
    if(old_first) old_first->prev = new_item;
    else list->last = new_item;
    list->first = new_item;
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if(item == nullptr) return list_insert(list, data);
    ListItem* old_next = item->next;
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->prev = item;
    new_item->next = old_next;
    item->next = new_item;
    if(old_next) old_next->prev = new_item;
    else list->last = new_item;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    ListItem* old_first = list->first;
    ListItem* new_first = old_first->next;
    list->first = new_first;
    if(new_first) new_first->prev = nullptr;
    else list->last = nullptr;
    delete old_first;
    return new_first;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if(item == nullptr) return list_erase_first(list);
    ListItem* new_item = item->next;
    if(new_item == nullptr) return nullptr;
    ListItem* next_item = new_item->next;
    item->next = next_item;
    if(next_item == nullptr) list->last = item;
    else next_item->prev = item;
    delete new_item;
    return next_item;
}
