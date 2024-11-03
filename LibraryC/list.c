#include "list.h"
#include <stdlib.h>


struct List_element {

    Data element;
    struct List_element *next;
    FFree *distruct;
};


struct List_operation {

    Data operation;
    struct List_operation *next;
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


List_operation *create_list_operation (List_operation **head, FFree f) {

    *head = (List_operation *)malloc(sizeof(List_operation));
    if (*head == NULL){
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


void delete_list_memory_opearation (List_operation **head){

    List_operation *temp = *head;
    List_operation *next;

    if(*head != NULL && (*head) -> distruct != NULL){
        while (temp != NULL){
            next = temp -> next;
            free(temp);
            temp = next;
        }
    }
    *head = NULL;
}
