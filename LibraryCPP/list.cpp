#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* pNext;

    ListItem(Data data, ListItem* next = nullptr) {
        this->data = data;
        this->pNext = next;
    }
};

struct List
{
    ListItem* head;
    ListItem* last;

    List() {
        head = nullptr;
        last = nullptr;
    }
    ~List() {
        ListItem* current = head;
        while (current) {
            ListItem *head = current->pNext;
            delete current;
            current = head;
        }
    }
};

//+
List *list_create()
{
    return new List;
}

void list_delete(List* list)
{
    // TODO: free items
    delete list;
}

//+
ListItem* list_first(List* list)
{
    return list->head;
}

//+
Data list_item_data(const ListItem* item){
    return (item == NULL) ? throw "NULL DATA" : item->data;
}

//+
ListItem* list_item_next(ListItem* item){
    return item->pNext;
}

ListItem* list_item_prev(ListItem* item)
{
    return NULL;
}

//+
ListItem* list_insert(List* list, Data data){
   if (list->head == nullptr) {
       return list->head = new ListItem(data);
   }
   else {
       ListItem* current = list->head;

       while (current->pNext != nullptr) {
           current = current->pNext;
       }

       current->pNext = new ListItem(data);
       list->last = current->pNext;

       return current->pNext;
   }
}

//+
ListItem* list_insert_after(List* list, ListItem* item, Data data){
    ListItem* previous = list->head;

    while (previous != item) {
        previous = previous->pNext;
    }

    ListItem *current = new ListItem(data, previous->pNext);

    previous->pNext = current;

    if (current->pNext == nullptr) {
        list->last = current;
    }

    return current;
}

//+
ListItem* list_erase(List* list, ListItem* item)
{
    if (item == list->head) {
        ListItem* temp = list->head;
        list->head = list->head->pNext;
        delete temp;
        return list->head;
    }
    else {
        ListItem* previous = list->head;
        while (previous->pNext != item) {
            previous = previous->pNext;
        }
        ListItem* current = previous->pNext;

        previous->pNext = current->pNext;

        if (previous->pNext == nullptr) {
            list->last = previous;
        }

        delete current;

        return previous->pNext;
    }
}

//+
ListItem* list_erase_next(List* list, ListItem* item){
    if (item == list->head) {
        ListItem* temp = list->head;
        list->head = list->head->pNext;
        delete temp;
        return list->head;
    }
    else {
        ListItem* previous = list->head;

        while (previous != item) {
            previous = previous->pNext;
        }

        ListItem* current = previous->pNext;

        previous->pNext = current->pNext;

        if (previous->pNext == nullptr) {
            list->last = previous;
        }

        delete current;

        return previous;
    }
}

//+
ListItem* list_last(List *list) {
    return (list->last == nullptr) ? list->head : list->last;
}

