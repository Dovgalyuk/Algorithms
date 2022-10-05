#include <cstddef>
#include "list.h"

struct ListItem
{
    Data value;
    ListItem *next;
    ListItem *prev;

    ListItem() {
        next = nullptr;
        prev = nullptr;
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
    while(list->head != nullptr) {
        list_erase(list, list->head);
    }
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
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *element = new ListItem;
    element->value = data;

    if (list->head != nullptr) {
        // элемент справа от нового => начало
        element->next = list->head;
        // элемент слева от начала => новый элемент
        list->head->prev = element;
    }
    // началу присваиваем адрес нового элемента
    list->head = element;
    return element;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *element = new ListItem;
    element->value = data;

    // элемент слева от нового => выбранный элемент
    element->prev = item;
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
    ListItem *tmp = nullptr;
    // Если список пустой
    if(list->head == nullptr) {
        return tmp;
    }
    // Если слева и справа от удаляемого элемента пусто
    if(item->next == nullptr && item->prev == nullptr) {
        list->head = nullptr;
        delete item;
        return tmp;
    }

    if (item->next == nullptr) { // Если справа от удаляемого элемента пусто
        // следующий элемент элемента слева от удаляемого => элемент справа от удаляемого
        item->prev->next = item->next;
        tmp = item->prev;
    } else if (item->prev == nullptr) { // Если слева от удаляемого элемента пусто
        // предыдущий элемент элемента справа от удаляемого => элемент слева от удаляемого
        item->next->prev = item->prev; 
        // tmp = item->next;
        list->head = item->next;
    } else {
        item->prev->next = item->next;
        item->next->prev = item->prev; 
        tmp = item->next;
    }

    delete item;
    return tmp;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if(item->prev == nullptr) {
        return list_erase(list, item->next);
    }
    return item;
}
