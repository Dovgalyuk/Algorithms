#include <cstddef>
#include "list.h"

struct ListItem
{
    Data value;
    ListItem* next;
};

struct List
{
    ListItem* head;
};

List* list_create()
{
    List* lst = new List;
    lst->head = nullptr;
    return lst;
}

void list_delete(List* list)
{
    if (!list)
        return;

    ListItem* cur = list->head;
    while (cur)
    {
        ListItem* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    delete list;
}

ListItem* list_first(List* list)
{
    return list ? list->head : nullptr;
}

Data list_item_data(const ListItem* item)
{
    return item ? item->value : Data();
}

ListItem* list_item_next(ListItem* item)
{
    return item ? item->next : nullptr;
}

ListItem* list_item_prev(ListItem* /*item*/)
{
    // Not supported for singly linked list
    return nullptr;
}

ListItem* list_insert(List* list, Data data)
{
    if (!list)
        return nullptr;
    auto* node = new ListItem{ data, list->head };
    list->head = node;
    return node;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (!list)
        return nullptr;

    if (item == nullptr)
    {
        // insert at beginning
        return list_insert(list, data);
    }
    auto* node = new ListItem{ data, item->next };
    item->next = node;
    return node;
}

ListItem* list_erase_first(List* list)
{
    if (!list || !list->head)
        return nullptr;

    ListItem* victim = list->head;
    ListItem* ret = victim->next;
    delete victim;
    list->head = ret;
    return ret;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (!list)
        return nullptr;
    if (item == nullptr)
    {
        // erase first
        return list_erase_first(list);
    }
    if (!item->next) return nullptr;
    ListItem* victim = item->next;
    item->next = victim->next;
    ListItem* ret = item->next;
    delete victim;
    return ret;
}
