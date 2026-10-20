#include <cstddef>
#include "list.h"
#include <string>
using namespace std;

struct ListItem
{
    Data data; 
    ListItem* prev;
    ListItem* next;
};  

struct List
{
    ListItem* head;
    ListItem* end;
};

List *list_create()
{
    List* list = new List;
    list->head = nullptr;
    list->end = nullptr;
    return list;
}

void list_delete(List *list)
{   
    ListItem* current = list->head;
    while(current!=nullptr){
        ListItem* next = current->next;
        delete current;
        current =  next;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list->head;
}

ListItem *list_last(List *list)
{
    return list->end;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* current = new ListItem;
    current->data = data;
    current->prev = nullptr;
    current->next = list->head;     

    if (list->head != nullptr) {
        list->head->prev = current;
    } else {
        list->end = current;         
    }

    list->head = current;
    return current;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if(item == nullptr){
        return list_insert(list, data);
    }

    ListItem* current = new ListItem;
    current->data = data;
    current->prev = item;
    current->next = item->next;

    if(item->next!=nullptr){
        item->next->prev = current;
    }
    else list->end = current;

    item->next = current;
    return current;
}

ListItem *list_erase_first(List *list)
{
    if(list->head == nullptr){
        return nullptr;
    }

    ListItem* first = list->head;
    list->head = first->next;

    if(list->head!=nullptr){
        list->head->prev = nullptr;
    }
    else list->end = nullptr;
    delete first;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{   
    if(item == nullptr || item->next == nullptr){
        return nullptr;
    }

    ListItem* nextElement = item->next;
    item->next = nextElement->next;
    if(nextElement->next!=nullptr){
        nextElement->next->prev = item;
    }
    else list->end = item;
    delete nextElement;
    return item->next;
}
