#include <stdlib.h>
#include "list.h"

struct ListItem
{
};

struct List
{
};

// создание списка
List *list_create()
{
    return NULL;
}

// удаление списка
void list_delete(List *list)
{
}

// получить первый элемент списка
ListItem *list_first(List *list)
{
    return NULL;
}

// извлечь данные из элемента списка
int list_item_data(ListItem *item)
{
    return 0;
}

// получить следующий элемент списка
ListItem *list_item_next(ListItem *item)
{
    return NULL;
}

// получить предыдущий элемент списка
ListItem *list_item_prev(ListItem *item)
{
    return NULL;
}

// вставить данные в начало списка
ListItem *list_insert(List *list, int data)
{
    return NULL;
}

// вставить данные после заданного элемента
ListItem *list_insert_after(List *list, ListItem *item, int data)
{
    return NULL;
}

// удалить заданный элемент списка
ListItem *list_erase(List *list, ListItem *item)
{
    return NULL;
}
