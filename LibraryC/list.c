#include "list.h"
#include <stdlib.h>


List_element *create_list_element (List_element **head, FFree f) {
    *head = (List_element *)malloc(sizeof(List_element));
    if(*head == NULL){
        return NULL;
    } else {
        (*head) -> distruct = f;
        (*head) -> next = NULL;
        return *head;
    }
}


void delete_list_memory_element (List_element **head){
    List_element *temp = *head;
    List_element *next;
    while (temp !=  NULL){
        next = temp -> next;
        free(temp);
        temp = next;
    }
    *head = NULL;
}


void add_list_element(List_element** head, char x) {
    List_element *new_element = (List_element *)malloc(sizeof(List_element));
    if (new_element != NULL) {
        new_element->element = x;
        new_element->next = *head;
        *head = new_element;
    }
}
