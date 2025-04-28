#include <cstddef>
#include "list.h"
#include <stdexcept>

struct ListItem
{
    Data data;             
    ListItem* prev;        
    ListItem* next;        
};

struct List
{
    ListItem* head;       
    ListItem* tail;        
    size_t size;
};

// Создание пустого списка
List *list_create()
{
    List* list = new List;
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
    return list;
}

// Удаление списка
void list_delete(List *list)
{
    ListItem* current = list->head;
    while (current) {
        ListItem* temp = current;
        current = current->next;
        delete temp;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list->head;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

// Следующий элемент
ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

// Предыдущий элемент
ListItem *list_item_prev(ListItem *item)
{
    return item->prev;
}


// Вставка элемента в начало списка
// Возвращает указатель на созданный элемент
 
ListItem *list_insert(List *list, Data data)
{
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->prev = nullptr;
    newItem->next = list->head;

    if (list->head) {
        list->head->prev = newItem;
    } else {
        list->tail = newItem;
    }
    list->head = newItem;
    list->size++;

    return newItem;
}


// Вставка элемента после указанного
// Если item == nullptr, вставляем в начало

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!item) {
        return list_insert(list, data);
    }

    ListItem* newItem = new ListItem;
    newItem->data = data;

    newItem->prev = item;
    newItem->next = item->next;
    if (item->next) {
        item->next->prev = newItem;
    } else {
        list->tail = newItem;
    }
    item->next = newItem;
    list->size++;

    return newItem;
}


// Удаление первого элемента
// Возвращает указатель на новый первый элемент (или nullptr, если список пуст)

ListItem *list_erase_first(List *list)
{
    if (!list->head) {
        return nullptr; 
    }
    ListItem* toDelete = list->head;
    list->head = toDelete->next;
    if (list->head) {
        list->head->prev = nullptr;
    } else {
        list->tail = nullptr;
    }
    delete toDelete;
    list->size--;
    return list->head;
}


// Удаление элемента, следующего за item
// Если item == nullptr, удаляем первый элемент
// Возвращает указатель на элемент, который стал стоять
// на месте удалённого (или nullptr, если список пуст или удаляемый элемент был последним).
 
ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!item) {
        return list_erase_first(list);
    }
    ListItem* toDelete = item->next;
    if (!toDelete) {
        return nullptr; 
    }

    item->next = toDelete->next;
    if (toDelete->next) {
        toDelete->next->prev = item;
    } else {
        list->tail = item;
    }
    delete toDelete;
    list->size--;
    return item->next;
}

size_t list_size(const List *list) {
    return list->size;
}

ListItem *list_get(const List *list, size_t index) {
    if (index >= list->size) {
        throw std::out_of_range("Index out of range");
    }

    ListItem *current = list->head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current;
}
