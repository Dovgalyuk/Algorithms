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
    ListItem *newItem = new ListItem(data, nullptr);

    newItem->nextItem = list->firstItem;

    list->firstItem = newItem;

    return newItem;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *newItem = new ListItem(data, item->nextItem);

    item->nextItem = newItem;

    if (newItem->nextItem == nullptr)
        list->lastItem = newItem;

    return newItem;
}

ListItem *list_erase(List *list, ListItem *item)
{
    return NULL;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem *tmp = nullptr;
    if(list->firstItem == nullptr || item->nextItem == nullptr) {
        return tmp;
    }
    tmp = item->nextItem;

    item->nextItem = item->nextItem->nextItem;

    delete tmp;

    return item->nextItem;
}

ListItem *list_erase_first(List *list) {
    ListItem* tmp = nullptr;
    tmp = list->firstItem;
    list->firstItem = list->firstItem->nextItem;

    delete tmp;

    return list->firstItem;
}
