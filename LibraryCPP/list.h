#ifndef LIST_H
#define LIST_H

struct ListItem {
    int data;
    ListItem* next;
    ListItem* prev;
};

struct List {
    ListItem* head;
    ListItem* tail;
};

// Создает новый список
List* list_create();

// Удаляет список
void list_delete(List* list);

// Вставляет элемент в начало списка
void list_insert(List* list, int data);

// Вставляет элемент после указанного узла
void list_insert_after(List* list, ListItem* item, int data);

// Удаляет первый элемент списка
void list_erase_first(List* list);

// Возвращает первый элемент списка
ListItem* list_first(const List* list);

// Возвращает данные из элемента списка
int list_item_data(const ListItem* item);

// Возвращает следующий элемент списка
ListItem* list_item_next(const ListItem* item);

#endif // LIST_H