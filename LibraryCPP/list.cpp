#include <cstddef>
#include "list.h"

using namespace std;
struct ListItem
{
    Data data;
    ListItem *next;
    ListItem *prev;
};

struct List
{
    ListItem *first;
    ListItem *last;
    size_t size;
};

List *list_create()
{
    List *list = new List;
    list->first = nullptr;
    list->last = nullptr;
    list->size = 0;
    return list;
}

void list_delete(List *list)
{
    if (list == nullptr) return;
    ListItem *cur = list->first;
    while (cur != nullptr) {
        ListItem *next = cur->next;
        delete cur;
        cur = next;
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
    ListItem *item = new ListItem;
    item->data = data;
    item->prev = nullptr;
    item->next = list->first;
    if (list->first != nullptr) {
        list->first->prev = item;
    } else {
        list->last = item;
    }
    list->first = item;
    list->size++;
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == nullptr) {
        return list_insert(list, data);
    }
    ListItem *newItem = new ListItem;
    newItem->data = data;
    newItem->prev = item;
    newItem->next = item->next;

    if (item->next != nullptr) {
        item->next->prev = newItem;
    } else {
        list->last = newItem;
    }
    item->next = newItem;
    list->size++;
    return newItem;
}

ListItem *list_erase_first(List *list)
{
    if (list->first == nullptr) {
        return nullptr;
    }
    ListItem *victim = list->first;
    ListItem *newFirst = victim->next;

    if (newFirst != nullptr) {
        newFirst->prev = nullptr;
    } else {
        list->last = nullptr;
    }
    list->first = newFirst;
    list->size--;
    delete victim;
    return newFirst;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr) {
        return list_erase_first(list);
    }
    ListItem *victim = item->next;
    if (victim == nullptr) {
        return nullptr;
    }
    ListItem *afterVictim = victim->next;
    item->next = afterVictim;
    if (afterVictim != nullptr) {
        afterVictim->prev = item;
    } else {
        list->last = item; 
    }
    list->size--;
    delete victim;
    return afterVictim;
}
