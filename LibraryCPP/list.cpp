#include <cstddef>
#include "list.h"

struct ListItem
{
    Data value;
    ListItem *next;

    ListItem() {
        next = nullptr;
    }
};

struct List
{
    ListItem *head;

    List() {
        head = nullptr;
    }
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    while(list->head->next != nullptr) {
        list_erase_next(list, list->head);
    }
    list_erase_head(list);
    delete list;
}

ListItem *list_first(List *list)
{
    return list->head;
}

Data list_item_data(const ListItem *item)
{
    return item->value;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    return NULL;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *element = new ListItem;
    element->value = data;

    if (list->head != nullptr) {
        // элемент справа от нового => начало
        element->next = list->head;
    }
    // началу присваиваем адрес нового элемента
    list->head = element;
    return element;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *element = new ListItem;
    element->value = data;

    // Если справа от выбранного элемента есть элемент
    if(item->next != nullptr) {
        // элемент справа от нового => элемент справа от выбранного
        element->next = item->next;
    }
    // элемент справа от выбранного => новый элемент
    item->next = element;
    return element;
}

ListItem *list_erase(List *list, ListItem *item)
{   
    return NULL;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem *tmp = nullptr;
    // Если список пустой 
    if(list->head == nullptr) {
        return tmp;
    }
    // Если справа пусто
    if(item->next == nullptr) {
        return tmp;
    }
    // Удаляемый элемент
    tmp = item->next;

    // Элемент слева от удаляемого => элемент справа
    item->next = item->next->next;

    delete tmp;
    return item->next;
}

ListItem *list_erase_head(List *list) {
    ListItem* tmp = nullptr;
    tmp = list->head;
    list->head = list->head->next;
    
    delete tmp;
    return list->head;
}