#ifndef LIST_H
#define LIST_H

// В списке хранятся данные типа int,
// поэтому функции принимают и возвращают 
// данные этого типа

struct List;
struct ListItem;

// создание списка
List *list_create();

// удаление списка
void list_delete(List *list);

// получить первый элемент списка
ListItem *list_first(List *list);

// извлечь данные из элемента списка
int list_item_data(ListItem *item);

// получить следующий элемент списка
ListItem *list_item_next(ListItem *item);

// получить предыдущий элемент списка
ListItem *list_item_prev(ListItem *item);

// вставить данные в начало списка
ListItem *list_insert(List *list, int data);

// вставить данные после заданного элемента
ListItem *list_insert_after(List *list, ListItem *item, int data);

// удалить заданный элемент списка
ListItem *list_erase(List *list, ListItem *item);

// удалить элемент списка, следующий за заданным
ListItem *list_erase_next(List *list, ListItem *item);

// получить последний элемент списка
ListItem *list_last(List *list);

#endif
