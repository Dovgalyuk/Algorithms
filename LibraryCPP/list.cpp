#include "list.h"
#include <cassert>
#include <cstddef>

struct ListItem {
    Data value;
    ListItem* prev;
    ListItem* next;
};

struct List {
    ListItem* head;
    std::size_t sz;
};

static ListItem* make_node(Data v, ListItem* p = nullptr, ListItem* n = nullptr) {
    return new ListItem{v, p, n};
}

List* list_create() {
    auto* lst = new List;
    lst->head = nullptr;
    lst->sz = 0;
    return lst;
}

void list_delete(List* list) {
    if (!list) return;
    auto* cur = list->head;
    while (cur) {
        auto* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    delete list;
}

ListItem* list_first(List* list) {
    return list ? list->head : nullptr;
}

Data list_item_data(const ListItem* item) {
    assert(item);
    return item->value;
}

ListItem* list_item_next(ListItem* item) {
    return item ? item->next : nullptr;
}

ListItem* list_item_prev(ListItem* item) {
    return item ? item->prev : nullptr;
}

ListItem* list_insert(List* list, Data data) {
    assert(list);
    auto* node = make_node(data, nullptr, list->head);
    if (list->head)
        list->head->prev = node;
    list->head = node;
    ++list->sz;
    return node;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    assert(list);
    if (!item)
        return list_insert(list, data);

    auto* node = make_node(data, item, item->next);
    if (item->next)
        item->next->prev = node;
    item->next = node;
    ++list->sz;
    return node;
}

ListItem* list_erase_first(List* list) {
    assert(list);
    if (!list->head)
        return nullptr;

    auto* del = list->head;
    auto* ret = del->next;
    if (ret)
        ret->prev = nullptr;
    list->head = ret;

    delete del;
    --list->sz;
    return ret;
}

ListItem* list_erase_next(List* list, ListItem* item) {
    assert(list);
    if (!item)
        return list_erase_first(list);

    auto* del = item->next;
    if (!del)
        return nullptr;

    auto* ret = del->next;
    item->next = ret;
    if (ret)
        ret->prev = item;

    delete del;
    --list->sz;
    return ret;
}
