#include <cstddef>
#include "list.h"

struct ListItem
{
    Data d;
    ListItem* n;
    ListItem* p;
};

struct List
{
    ListItem* h;
};

List *list_create()
{
    List* list = new List;
    list->h = nullptr;
    return list;
}

void list_delete(List *list)
{
    if(!list) return;

    ListItem* head = list->h;
    if(head != nullptr){
        ListItem* cur = head->n;
        while(cur && cur != head){
            ListItem* next = cur->n;
            delete cur;
            cur = next;
        }
        delete head;
        list->h = nullptr;
    }

    delete list;
}

ListItem *list_first(List *list)
{
    if(!list) return nullptr;
    return list->h;
}

Data list_item_data(const ListItem *item)
{
    if(!item) return "";
    return item->d;
}

ListItem *list_item_next(ListItem *item)
{
    if(!item) return nullptr;
    return item->n;
}

ListItem *list_item_prev(ListItem *item)
{
    if(!item) return nullptr;
    return item->p;
}

ListItem *list_insert(List *list, Data data)
{
    if(!list) return nullptr;
    ListItem* newIt = new ListItem;
    newIt->d = data;

    if(list->h == nullptr){
        newIt->n = newIt;
        newIt->p = newIt;
        list->h = newIt;
    } 
    else {
        ListItem* tail = list->h->p;

        newIt->n = list->h;
        newIt->p = tail;
        tail->n = newIt;
        list->h->p = newIt;
        list->h = newIt;
    }
    return newIt;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if(!list) return nullptr;

    if(list->h == nullptr || item == nullptr) return list_insert(list, data);

    ListItem* newIt = new ListItem;
    newIt->d = data;

    ListItem* next = item->n;
    newIt->n = next;
    newIt->p = item;

    item->n = newIt;
    next->p = newIt;

    return newIt;
}

ListItem *list_erase_first(List *list)
{
    if(!list || !list->h) return nullptr;

    ListItem* del = list->h;
    ListItem* next = del->n;

    if(del == next){
        list->h = nullptr;
        delete del;
        return nullptr;
    }

    ListItem* prev = del->p;

    prev->n = next;
    next->p = prev;

    list->h = next;

    delete del;

    return next;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if(!list || !list->h) return nullptr;

    ListItem* del = (item == nullptr) ? list->h : item->n;
    ListItem* next = del->n;

    if(del == next){
        list->h = nullptr;
        delete del;
        return nullptr;
    }

    del->p->n = del->n;
    del->n->p = del->p;

    if(del == list->h) list->h = next;

    delete del;

    return next;
}
