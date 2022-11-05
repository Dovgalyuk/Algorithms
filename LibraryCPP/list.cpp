#include <cstddef>
#include "list.h"

struct ListItem{
    Data data;
    ListItem* pNext;

    ListItem(Data data, ListItem* next = nullptr) {
        this->data = data;
        this->pNext = next;
    }
};

struct List{
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

List *list_create(){
    return new List;
}

void list_delete(List* list){
    // TODO: free items
    delete list;
}

ListItem* list_first(List* list){
    return list->head;
}

Data list_item_data(const ListItem* item){
    return (item == NULL) ? throw "NULL DATA" : item->data;
}

ListItem* list_item_next(ListItem* item){
    return item->pNext;
}

ListItem* list_item_prev(ListItem* item){
    return NULL;
}

ListItem* list_insert(List* list, Data data){
    ListItem* add_item = new ListItem(data, list->head);

    if (!list->head) list->last = add_item;

    return list->head = add_item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data){
    ListItem * add_item = new ListItem(data, item->pNext);

    item->pNext = add_item;

    if (add_item->pNext == nullptr) list->last = add_item;

    return add_item;
}

ListItem* list_erase(List* list, ListItem* item){
    if (item == list->head) {
        ListItem* temp = list->head;
        list->head = list->head->pNext;
        delete temp;
        return list->head;
    }
    else {
        ListItem* current = item->pNext;

        item->pNext = current->pNext;

        if (item->pNext == nullptr) list->last = item;

        delete current;

        return item->pNext;
    }
}

ListItem* list_erase_next(List* list, ListItem* item){
    if (item == list->head) {
        ListItem* temp = list->head;
        list->head = list->head->pNext;
        delete temp;
        return list->head;
    }
    else {
        ListItem* current = item->pNext;

        item->pNext = current->pNext;

        if (item->pNext == nullptr) list->last = item;

        delete current;

        return item;
    }
}

ListItem* list_last(List* list) {
    return (list->last == nullptr) ? list->head : list->last;
}

