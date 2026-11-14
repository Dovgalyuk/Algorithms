#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
    ListItem *prev;
    bool is_sentinel;
};

struct List
{
    ListItem dummy;
};

static ListItem *insert_after_node(ListItem *pos, Data data)
{
    ListItem *item = new ListItem;
    item->data = data;
    item->is_sentinel = false;
    item->prev = pos;
    item->next = pos->next;
    pos->next->prev = item;
    pos->next = item;
    return item;
}

List *list_create()
{
    List *list = new List;
    list->dummy.data = (Data)0;
    list->dummy.is_sentinel = true;
    list->dummy.next = &list->dummy;
    list->dummy.prev = &list->dummy;
    return list;
}

void list_delete(List *list)
{

    while (list_erase_first(list) != NULL) {
    }
    while (list_first(list) != NULL)
        list_erase_first(list);
    delete list;
}

ListItem *list_first(List *list)
{
    ListItem *item = list->dummy.next;
    return item->is_sentinel ? NULL : item;
}

ListItem *list_last(List *list)
{
    ListItem *item = list->dummy.prev;
    return item->is_sentinel ? NULL : item;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next->is_sentinel ? NULL : item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    return item->prev->is_sentinel ? NULL : item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    return insert_after_node(&list->dummy, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    (void)list;
    return insert_after_node(item, data);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    (void)list;
    ListItem *victim = item->next;
    if (victim->is_sentinel)
        return NULL;
    item->next = victim->next;
    victim->next->prev = item;
    delete victim;

    return item->next->is_sentinel ? NULL : item->next;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, &list->dummy);
}