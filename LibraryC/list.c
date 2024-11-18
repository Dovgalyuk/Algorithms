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
    while (temp !=  NULL){
        next = temp -> next;
        free(temp);
        temp = next;
    }
    *head = NULL;
}


void add_list_element(List_element **head, char x) {
    List_element *new_element = (List_element *)malloc(sizeof(List_element));
    if (new_element != NULL) {
        new_element -> element = x;
        new_element -> next = *head;
        *head = new_element;
    }
}


Data pop_list (List_element **head) {
    if(*head == NULL) {
        return '\0';
    } else {
        List_element *top_element = *head;
        Data element = top_element -> element;
        *head = top_element -> next;
        free(top_element);
        return element;
    }
}


void add_list_element(List_element **head, char x) {
    List_element *new_element = (List_element *)malloc(sizeof(List_element));
    if (new_element != NULL) {
        new_element -> element = x;
        new_element -> next = *head;
        *head = new_element;
    }
}



