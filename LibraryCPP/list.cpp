#include <cstddef>
#include "stack.h"
#include "list.h"

using namespace std;

struct ListItem
{
    Data data;
    ListItem* next;
};

struct List
{
    ListItem* begin;
    ListItem* end;
};

List* list_create()
{
    List* list = new List;
    list->begin = nullptr;
    list->end = nullptr;
    return list;
}

void list_delete(List* list)
{
    ListItem* current = list->begin;
    while (current != nullptr)
    {
        ListItem* temp = current->next;
        delete current;
        current = temp;
    }
    delete list;
}

ListItem* list_first(List* list)
{
    return list->begin;
}

Data list_item_data(const ListItem* item)
{
    return item->data;
}

ListItem* list_item_next(ListItem* item)
{
    return item->next;
}

//ListItem *list_item_prev(ListItem *item)
//{
//    return NULL;
//}

ListItem* list_insert(List* list, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = list->begin;
    list->begin = new_item;
    if (list->end == nullptr) {
        list->end = new_item;
    }
    return new_item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    item->next = new_item;
    if (item == list->end) {
        list->end = new_item;
    }
    return new_item;
}

ListItem* list_erase_first(List* list)
{
    if (list->begin != nullptr) {
        ListItem* first = list->begin;
        list->begin = list->begin->next;
        if (list->begin == nullptr) {
            list->end = nullptr;
        }
        delete first;
    }
    return list->begin;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (item->next != nullptr) {
        ListItem* next = item->next;
        item->next = item->next->next;
        if (item->next == nullptr) {
            list->end = item;
        }
        delete next;
    }
    return item->next;
}
