#include <stdlib.h>
#include "list.h"

struct ListItem {
    Data data;
    ListItem *prev;
    ListItem *next;
};

struct List {
    ListItem *head;
    FFree *free_fn;
};

List *list_create(FFree f)
{
    List *list = malloc(sizeof(struct List));
    if (!list) return NULL;
    list->head = NULL;
    list->free_fn = f;
    return list;
}

static void list_free_item(const List *list, ListItem *item)
{
    if (!item) return;
    if (list->free_fn) {
        void *p = item->data;
        list->free_fn(p);
    }
    free(item);
}

void list_delete(List *list)
{
    if (!list) return;
    ListItem *it = list->head;
    while (it) {
        ListItem *next = it->next;
        list_free_item(list, it);
        it = next;
    }
    free(list);
}

ListItem *list_first(const List *list)
{
    return list ? list->head : NULL;
}

Data list_item_data(const ListItem *item)
{
    return item ? item->data : (Data)0;
}

ListItem *list_item_next(const ListItem *item)
{
    return item ? item->next : NULL;
}

ListItem *list_item_prev(const ListItem *item)
{
    return item ? item->prev : NULL;
}

ListItem *list_insert(List *list, const Data data)
{
    if (!list) return NULL;
    ListItem *item = malloc(sizeof(ListItem));
    if (!item) return NULL;
    item->data = data;
    item->prev = NULL;
    item->next = list->head;
    if (list->head) {
        list->head->prev = item;
    }
    list->head = item;
    return item;
}

ListItem *list_insert_after(List *list, ListItem *pos, const Data data)
{
    if (!list) return NULL;
    if (!pos) {
        return list_insert(list, data);
    }
    ListItem *item = malloc(sizeof(ListItem));
    if (!item) return NULL;
    item->data = data;
    item->prev = pos;
    item->next = pos->next;
    if (pos->next) {
        pos->next->prev = item;
    }
    pos->next = item;
    return item;
}

ListItem *list_erase_first(List *list)
{
    if (!list || !list->head) return NULL;
    ListItem *to_delete = list->head;
    ListItem *next = to_delete->next;
    if (next) next->prev = NULL;
    list->head = next;
    list_free_item(list, to_delete);
    return next;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list) return NULL;
    if (!item) {
        return list_erase_first(list);
    }
    ListItem *to_delete = item->next;
    if (!to_delete) return NULL;
    ListItem *next = to_delete->next;
    item->next = next;
    if (next) next->prev = item;
    list_free_item(list, to_delete);
    return next;
}

size_t list_size(const List *list)
{
    if (!list) return 0;
    size_t count = 0;
    for (ListItem *it = list->head; it; it = it->next) {
        count++;
    }
    return count;
}
