#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
};

struct List
{
    ListItem* head = nullptr;
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    while (list->head) {
        ListItem* temp = list->head;
        list->head = list->head->next;
        delete temp;
    }
    // TODO: free items
    delete list;
}

ListItem *list_first(List *list)
{
    return list->head;;
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
    return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* item = new ListItem{ data, list->head };
    list->head = item;
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!item) {
        return list_insert(list, data);
    }
    ListItem* newItem = new ListItem{ data, item->next };
    item->next = newItem;
    return newItem;
}

ListItem *list_erase_first(List *list)
{
    if (!list->head) {
        return nullptr;
    }
    ListItem* temp = list->head;
    list->head = temp->next;
    delete temp;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!item) {
        return list_erase_first(list);
    }
    if (!item->next) {
        return nullptr;
    }
    ListItem* temp = item->next;
    item->next = temp->next;
    delete temp;
    return item->next;
}
