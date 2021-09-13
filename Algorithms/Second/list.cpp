#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next = nullptr;
    ListItem* prev = nullptr;

    ListItem(Data data): data(data) {};
};

struct List
{
    ListItem* first = nullptr;
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    ListItem* item = list->first;
    while (item) {
        ListItem* deleted = item;
        item = item->next;
        delete deleted;
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
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* item = new ListItem(data);
    item->next = list->first;
    if (list->first) {
        list->first->prev = item;
    }
    list->first = item;
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem* new_item = new ListItem(data);
    new_item->next = item->next;
    if (new_item->next) {
        new_item->next->prev = new_item;
    }
    item->next = new_item;
    new_item->prev = item;
    return new_item;
}

ListItem *list_erase(List *list, ListItem *item)
{
    if (list->first == item) {
        list->first = item->next;
    }
    if (item->next) {
        item->next->prev = item->prev;
    }
    if (item->prev) {
        item->prev->next = item->next;
    }
    return item;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem* next = item->next;
    if (next->next) {
        next->next->prev = item;
        item->next = next->next;
    }
    return item;
}
