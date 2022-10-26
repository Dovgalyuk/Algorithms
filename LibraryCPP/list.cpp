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

//Create array
List *list_create()
{
    return new List;
}

//delete array
void list_delete(List* list)
{
    // TODO: free items
    delete list;
}

//return first element
ListItem* list_first(List* list)
{
    return list->head;
}

//return the data of an element
Data list_item_data(const ListItem* item){
    return item->data;
}

//return next item
ListItem* list_item_next(ListItem* item){
    return item->pNext;
}


//insert item
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

//delete element
ListItem* list_erase(List* list, ListItem* item)
{
    ListItem* temp = list->head;
    list->head = list->head->pNext;
    delete temp;
    return list->head;
}

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

        delete current;

        return previous->pNext;
    }
}

ListItem* list_last(List *list) {
    return (list->last == nullptr) ? list->head : list->last;
}