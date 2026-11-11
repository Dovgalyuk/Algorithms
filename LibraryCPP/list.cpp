#include <cstddef>
#include "list.h"

struct ListItem
{
    ListItem* nextItem;
    Data item;
};

struct List
{
    ListItem* firstItem;
    ListItem* lastItem;
};

List *list_create()
{
    return new List{nullptr, nullptr};
}

void list_delete(List *list)
{
    ListItem* current = list->firstItem;

    while(current != nullptr){
        ListItem* next = current->nextItem;
        delete current;
        current = next;
    }

    delete list;
}

ListItem *list_first(List *list)
{
    return list->firstItem;
}

ListItem *list_last(List *list)
{
    return list->lastItem;
}

Data list_item_data(const ListItem *item)
{
    return item->item;
}

ListItem *list_item_next(ListItem *item)
{
    return item->nextItem;
}

ListItem *list_item_prev(ListItem *item)
{
    return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    if(list->firstItem == nullptr && list->lastItem == nullptr){
        ListItem* firstItem = new ListItem{nullptr, data};
        list->firstItem = firstItem;
        list->lastItem = firstItem;
        return firstItem;
    }else{
        ListItem* firstItemOld = list->firstItem;
        ListItem* firstItemNew = new ListItem{firstItemOld, data};
        list->firstItem = firstItemNew;
        return firstItemNew;
    }
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == nullptr || list->firstItem == nullptr) {
        return list_insert(list, data);
    }
    else{
        ListItem* itemNew = new ListItem{item->nextItem, data};

        if (item == list->lastItem) {
            list->lastItem = itemNew;
        }

        item->nextItem = itemNew;
        return itemNew;
    }
}

ListItem *list_erase_first(List *list)
{
    if(list == nullptr){
        return nullptr;
    }
    else if(list->firstItem == list->lastItem){
        delete list->firstItem;
        list->firstItem = nullptr;
        list->lastItem = nullptr;
        return nullptr;
    }
    else{
        ListItem* firstItemOld = list->firstItem;
        ListItem* firstItemNew = firstItemOld->nextItem;

        list->firstItem = firstItemNew;

        delete firstItemOld;

        return firstItemNew;
    }
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if(item == nullptr){
        return list_erase_first(list);
    } else if(item->nextItem == nullptr){
        return nullptr;
    }else{
        ListItem* deletedItem = item->nextItem;
        item->nextItem = deletedItem->nextItem;
        if(deletedItem == list->lastItem){
            list->lastItem = item;
        }
        delete deletedItem;
        return item->nextItem;
    }
}
