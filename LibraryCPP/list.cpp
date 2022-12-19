#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *nextItem;

    ListItem(Data data, ListItem * nextItem) {
        this->data = data;
        this->nextItem = nextItem;
    }
};

struct List
{
    ListItem *firstItem;
    ListItem *lastItem;

    List() {
        this->firstItem = nullptr;
        this->lastItem = nullptr;
    }

    ~List() {
        ListItem* currentItem = this->firstItem;
        while (currentItem) {
            ListItem* nextItem = currentItem->nextItem;
            delete currentItem;
            currentItem = nextItem;
        }
    }
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    delete list;
}

ListItem *list_first(List *list)
{
    return list->firstItem;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item->nextItem;
}

ListItem *list_item_prev(ListItem *item)
{
    return NULL;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* newItem = new ListItem(data, nullptr);

    newItem->nextItem = list->firstItem;

    if(!list->firstItem)
        list->lastItem = newItem;

    return list->firstItem = newItem;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem* newItem = new ListItem(data, item->nextItem);

    if (item == list->lastItem)
        list->lastItem = newItem;

    return item->nextItem = newItem;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item->nextItem) {
        ListItem* next = item->nextItem->nextItem;
        delete item->nextItem;
        return item->nextItem = next;
    }

    if (item->nextItem == list->lastItem) {
        delete list->lastItem;
        return list->lastItem = item;
    }

    return 0;

}

ListItem *list_erase(List *list, ListItem *item)
{
    return NULL;
}


ListItem *list_erase_first(List *list) {
    ListItem* tmp = nullptr;
    tmp = list->firstItem;
    list->firstItem = list->firstItem->nextItem;

    delete tmp;

    return list->firstItem;
}
