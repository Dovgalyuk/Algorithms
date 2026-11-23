#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
    bool sentinel = false;
};

struct List
{
    ListItem* head;
    ListItem* tail;
};

List *list_create()
{
    List* list = new List;
    list->head = new ListItem;
    list->head->sentinel = true;
    list->head->next = list->head;
    list->tail = list->head;
    return list;
}

void list_delete(List *list)
{
    if (!list) return;
    ListItem* cur = list->head->next;
    while (cur != list->head) {
        ListItem* next = cur->next;
        delete cur;
        cur = next;
    }
    delete list->head;
    delete list;
}

ListItem *list_first(List *list)
{
    if (!list) return NULL;
    if (list->head->next == list->head) return NULL;
    return list->head->next;
}

ListItem *list_last(List *list)
{
    if (!list) return NULL;
    if (list->tail == list->head) return NULL;
    return list->tail;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem* list_item_next(ListItem* item)
{
    if (item == nullptr || item->next->sentinel)
        return nullptr;

    return item->next;
}

ListItem* list_item_prev(ListItem*)
{
    return nullptr;
}

ListItem* list_insert(List* list, Data data)
{
    return list_insert_after(list, list->head, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem* prev = item ? item : list->head;

    ListItem* node = new ListItem;
    node->data = data;
    node->next = prev->next;
    prev->next = node;
    if (prev == list->tail)
        list->tail = node;

    return node;
}

ListItem* list_erase_first(List* list)
{
    return list_erase_next(list, list->head);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem* prev = item ? item : list->head;

    ListItem* victim = prev->next;

    if (victim == list->head) return NULL;
    prev->next = victim->next;

    if (victim == list->tail)
        list->tail = (prev == list->head) ? list->head : prev;

    ListItem* after = prev->next;
    delete victim;

    if (after == list->head) return NULL;
    return after;
}
