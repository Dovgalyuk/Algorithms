#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
};

struct List
{
    ListItem* head;
    ListItem* tail;
};

List *list_create()
{
    List* list = new List;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void list_delete(List *list)
{
    
    // TODO: free items
    if (!list) return;

    ListItem* current = list->head;
    while (current != nullptr)
    {
        ListItem* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    if (!list) return NULL;
    return list->head;
}

ListItem *list_last(List *list)
{
    if (!list) return NULL;
    return list->tail;
}

Data list_item_data(const ListItem *item)
{
    if (!item) return (Data)0;
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if (!item) return NULL;
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    (void)item;
    return NULL;
}

ListItem *list_insert(List *list, Data data)
{
    if (!list) return NULL;
    ListItem* node = new ListItem;
    node->data = data;
    node->next = list->head;
    list->head = node;
    if (!list->tail)
    {
        list->tail = node;
    }
    return node;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list) return NULL;
    if (!item)
    {
        return list_insert(list, data);
    }
    ListItem* node = new ListItem;
    node->data = data;
    node->next = item->next;
    item->next = node;
    if (item == list->tail)
    {
        list->tail = node;
    }
    return node;
}

ListItem *list_erase_first(List *list)
{
    if (!list || !list->head) return nullptr;

    ListItem* temp = list->head;
    list->head = list->head->next;

    if (list->head == nullptr)
    {
        list->tail = nullptr;
    }

    delete temp;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list) return NULL;
    if (!item)
    {
        return list_erase_first(list);
    }
    if (!item->next) return NULL;

    ListItem* node = item->next;
    item->next = node->next;

    if (node == list->tail)
    {
        list->tail = item;
    }

    delete node;
    return item->next;
}
