#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
    ListItem(Data data) : data(data), next(nullptr) {}
};

struct List
{
    ListItem* head;
    List() : head(nullptr) {}
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    while (list->head != nullptr)
    {
        ListItem* temp = list->head;
        list->head = list->head->next;
        delete temp;
    }
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

ListItem *list_item_prev(ListItem *item)
{
    return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* newItem = new ListItem(data);
    newItem->data = data;
    newItem->next = list->head;
    list->head = newItem;
    return newItem;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == nullptr) {
        return list_insert(list, data);
    }
    ListItem* newItem = new ListItem(data);
    newItem->data = data;
    newItem->next = item->next;
    item->next = newItem;
    return newItem;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == nullptr) {
        return nullptr;
    }
    ListItem *old_head = list->head;
    list->head = list->head->next;
    delete old_head;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr || item->next == nullptr) {
        return nullptr;
    }
    ListItem *to_delete = item->next;
    item->next = to_delete->next;
    delete to_delete;
    return item->next;
}
