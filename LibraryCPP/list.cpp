#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* prev;
    ListItem* next;
    bool is_sentinel;
};

struct List
{
    ListItem* head;
    size_t size;
};

List* list_create()
{
    List* l = new List;
    l->head = new ListItem;
    l->head->prev = l->head;
    l->head->next = l->head;
    l->head->data = Data();
    l->head->is_sentinel = true;
    l->size = 0;
    return l;
}

void list_delete(List* list)
{
    if (!list) return;
    ListItem* cur = list->head->next;
    while (cur != list->head) {
        ListItem* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    delete list->head;
    delete list;
}

ListItem* list_first(List* list)
{
    if (list == nullptr || list->size == 0) return nullptr;
    return list->head->next;
}

ListItem* list_last(List* list)
{
    if (list == nullptr || list->size == 0) return nullptr;
    return list->head->prev;
}

Data list_item_data(const ListItem* item)
{
    if (item != nullptr) return item->data;
    return Data();
}

ListItem* list_item_next(ListItem* item)
{
    if (item == nullptr || item->next == nullptr || item->next->is_sentinel) return nullptr;
    return item->next;
}

ListItem* list_item_prev(ListItem* item)
{
    if (item == nullptr || item->prev == nullptr || item->prev->is_sentinel) return nullptr;
    return item->prev;
}

ListItem* list_insert(List* list, Data data)
{
    if (list == nullptr) return nullptr;
    ListItem* node = new ListItem;
    node->data = data;
    node->is_sentinel = false;
    node->prev = list->head;
    node->next = list->head->next;
    list->head->next->prev = node;
    list->head->next = node;
    list->size++;
    return node;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (list == nullptr) return nullptr;
    if (item == nullptr) return list_insert(list, data);
    ListItem* node = new ListItem;
    node->data = data;
    node->is_sentinel = false;
    node->prev = item;
    node->next = item->next;
    item->next->prev = node;
    item->next = node;
    list->size++;
    return node;
}

ListItem* list_erase_first(List* list)
{
    if (list == nullptr || list->size == 0) return nullptr;
    ListItem* victim = list->head->next;
    ListItem* after = victim->next;
    victim->prev->next = victim->next;
    victim->next->prev = victim->prev;
    list->size--;
    delete victim;
    if (list->size == 0 || after->is_sentinel) return nullptr;
    return after;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (list == nullptr || list->size == 0) return nullptr;
    ListItem* victim;
    if (item == nullptr) {
        victim = list->head->next;
    }
    else {
        victim = item->next;
        if (victim->is_sentinel) return nullptr;
    }
    ListItem* after = victim->next;
    victim->prev->next = victim->next;
    victim->next->prev = victim->prev;
    list->size--;
    delete victim;
    if (list->size == 0 || after->is_sentinel) return nullptr;
    return after;
}