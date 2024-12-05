#include <cstddef>
#include "list.h"

struct ListItem
{
    Data * dt;
    ListItem * next;
};

struct List
{
    ListItem * first;
};

List *list_create()
{
    List * new_list = new List;
    new_list->first = nullptr;
    return new_list;
}

void list_delete(List *list)
{
    if (list != 0 && list != nullptr){
        ListItem * current = list->first;
        ListItem * temp;
        while (current != nullptr){
            temp = current;
            current = current->next;
            delete temp->dt;
            delete temp;
        }
        delete list;
    }
}

ListItem *list_first(List *list)
{
    if (list != 0 && list != nullptr){
        return list->first;
    }
    else return nullptr;
}

Data list_item_data(const ListItem *item) 
{
    return *(item->dt); 
}

ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

/*ListItem* list_item_prev(ListItem* item)
{
    return nullptr;
}*/

ListItem *list_insert(List *list, Data data)
{
    if (list != 0 && list != nullptr){
        ListItem * temp = new ListItem();
        temp->dt = new Data();
        *(temp->dt) = data;
        temp->next = list->first;
        list->first = temp;
        return temp;
    }
    else return nullptr;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (list != 0 && list != nullptr){
        ListItem * back = item->next;
        ListItem * temp = new ListItem();
        temp->dt = new Data();
        *(temp->dt) = data;
        item->next = temp;
        temp->next = back;
        return temp;
    }
    else return nullptr;
}

ListItem *list_erase_first(List *list)
{
    if (list != 0 && list != nullptr){
        if (list->first != nullptr){
            ListItem * temp = list->first;
            list->first = list->first->next;
            delete temp->dt;
            delete temp;
            return list->first;
        }
        else return nullptr;
    }
    else return nullptr;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (list != 0 && list != nullptr){
        if (item != nullptr && item->next != nullptr){
            ListItem * temp = item->next;
            item->next = temp->next;
            delete temp->next->dt;
            delete temp;
            return item->next;
        }
        else return nullptr;
    }
    else return nullptr;
}        
