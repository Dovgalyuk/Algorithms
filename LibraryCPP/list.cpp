#include <cstddef>
#include "list.h"
#include <iostream>

struct ListItem
{
    Data data;
    ListItem* next;
    ListItem()
    {
        data = NULL;
        next = nullptr;
    }
};

struct List
{
    ListItem* top;
    List()
    {
        top = nullptr;
    }
};

List *list_create()
@@ -16,23 +29,31 @@ List *list_create()

void list_delete(List *list)
{
    if (list->top != nullptr)
    {
        while (list->top->next != nullptr)
        {
            list_erase_next(list, list->top);
        }
        list_erase_top(list);
    }
    // TODO: free items
    delete list;
}

ListItem *list_first(List *list)
{
    return NULL;
    return list->top;
}

Data list_item_data(const ListItem *item)
{
    return (Data)0;
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return NULL;
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
@@ -42,20 +63,55 @@ ListItem *list_item_prev(ListItem *item)

ListItem *list_insert(List *list, Data data)
{
    return NULL;
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = list->top;
    list->top = newItem;
    return newItem;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    return NULL;
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = item->next;
    item->next = newItem;
    return newItem;
}

ListItem *list_erase(List *list, ListItem *item)
{
    if (item == list_first(list))
    {
        return list_erase_top(list);
    }
    else
    {
        std::cout << "Not applicable for the singly linked lists";
    }
    return NULL;
}

ListItem *list_erase_next(List *list, ListItem *item)
ListItem* list_erase_first(List* list)
{
    return NULL;
    if (list->top == nullptr)
    {
        return list->top;
    }
    ListItem* tmpItem = list->top;
    list->top = list_item_next(tmpItem);
    delete tmpItem;
    return list->top;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (item->next == nullptr)
    {
        return item->next;
    }
    ListItem* tmpItem = item->next;
    item->next = tmpItem->next;
    delete tmpItem;
    return item->next;
}
