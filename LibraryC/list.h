#ifndef LIST_H
#define LIST_H

typedef char Data;
typedef void (FFree)(void*);


typedef struct List_element List_element;


#ifdef __cplusplus
extern "C" {
#endif


List_element *create_list_element (List_element **head, FFree f);

void delete_list_memory_element (List_element **head);

void add_list_element(List_element** head, char x);

void add_list_element(List_element** head, char x);

Data pop_list (List_element **head);

#ifdef __cplusplus
}
#endif

#endif
