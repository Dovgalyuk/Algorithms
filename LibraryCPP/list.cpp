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
    while (list->head)
    {
        list_erase_first(list);
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
    insertItem->pNext = list->head;

    list->head = insertItem;
    return list->head;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    list = list;
    if (item) {
        ListItem* insertItem = new ListItem;
        insertItem->data = data;
        insertItem->pNext = item->pNext;
        item->pNext = insertItem;
    } 
    return item->pNext;   
}

ListItem *list_erase_first(List *list)
{
    if (list->head) {
        ListItem* old_head = list->head;
        list->head = old_head->pNext;
        delete old_head;
    }
    
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item && item->pNext) {
        ListItem* deleteItemNext = item->pNext->pNext;

        delete item->pNext;
        item->pNext = deleteItemNext;
    }

    return list->head;
}
