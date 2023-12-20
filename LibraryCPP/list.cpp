#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* pNext;
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
    ListItem* curr = list->head;
    ListItem* next;
    while (curr)
    {
        next = curr->pNext;
        delete curr;
        curr = next;
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
    return item->pNext;
}

ListItem *list_item_prev(ListItem *item)
{
    //список односвязный, поэтому в предыдущий элемент с текущими параметрами не попасть
    return item;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* insertItem = new ListItem;
    insertItem->data = data;
    insertItem->pNext = nullptr;
    if (list->head) {
        ListItem* temp = list->head;
        list->head = insertItem;
        insertItem->pNext = temp;
    } else {
        list->head = insertItem;
        
    }
    return list->head;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item) {
        ListItem* insertItem = new ListItem;
        insertItem->data = data;
        if (item->pNext) {
            insertItem->pNext = item->pNext;
            item->pNext = insertItem;
        } else {
            item->pNext = insertItem;
            insertItem->pNext = nullptr;
        }
    }
    return list->head;
}

ListItem *list_erase_first(List *list)
{
    ListItem* headNext = list->head->pNext;
    delete list->head;
    list->head = headNext;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item && item->pNext) {
        if (item->pNext->pNext) {
            ListItem* deleteItemNext = item->pNext->pNext;
            delete item->pNext;
            item->pNext = deleteItemNext;
        }
        else {
            delete item->pNext;
            item->pNext = nullptr;
        }
    }

    return list->head;
}
