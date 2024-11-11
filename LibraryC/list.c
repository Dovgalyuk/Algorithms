#include "list.h"
#include <stdlib.h>


struct List_element {
    Data element;
    struct List_element *next;
    FFree *distruct;
};



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
    if(*head != NULL && (*head) -> distruct != NULL){
        while (temp !=  NULL){
            next = temp -> next;
            free(temp);
            temp = next;
        }
    }
    *head = NULL;
}


