#ifndef LIST_H
#define LIST_H

typedef char Data;
typedef void (FFree)(void*);

typedef struct List_element List_element;
typedef struct List_operation List_operation;

#ifdef __cplusplus
extern "C" {
#endif

List_operation *create_list_operation (List_operation **head, FFree f);
List_element *create_list_element (List_element **head, FFree f);

void delete_list_memory_element (List_element **head);
void delete_list_memory_opearation (List_operation **head);


void add_list_element(List_element** head, char x);
void add_list_operations(List_operation** head, char x);


#ifdef __cplusplus
}
#endif

#endif
