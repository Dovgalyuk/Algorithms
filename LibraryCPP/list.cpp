#include "list.h"

using namespace std;

struct ListItem
{
    Data data;
    ListItem *next;
    ListItem *prev;
    bool dummy;
};

struct List
{
    ListItem head;
};

List *list_create()
{
    List *list = new List;
    list->head = {0, &list->head, &list->head, true};
    return list;
}

void list_delete(List *list)
{
    if (list == nullptr)
        return;

    while (list_first(list) != nullptr)
        list_erase_first(list);

    delete list;
}

ListItem *list_first(List *list)
{
    if (list == nullptr || list->head.next == &list->head)
        return nullptr;

    return list->head.next;
}

ListItem *list_last(List *list)
{
    if (list == nullptr || list->head.prev == &list->head)
        return nullptr;

    return list->head.prev;
}

Data list_item_data(const ListItem *item)
{
    return item == nullptr ? 0 : item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if (item == nullptr || item->next->dummy)
        return nullptr;

    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    if (item == nullptr || item->prev->dummy)
        return nullptr;

    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    return list_insert_after(list, nullptr, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (list == nullptr)
        return nullptr;

    if (item == nullptr)
        item = &list->head;

    ListItem *added = new ListItem{data, item->next, item, false};
    item->next->prev = added;
    item->next = added;
    return added;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, nullptr);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (list == nullptr)
        return nullptr;

    if (item == nullptr)
        item = &list->head;

    ListItem *removed = item->next;
    if (removed == &list->head)
        return nullptr;

    item->next = removed->next;
    removed->next->prev = item;
    delete removed;
    return list_item_next(item);
}
