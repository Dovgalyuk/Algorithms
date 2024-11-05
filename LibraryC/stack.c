#include "list.h"
#include "stack.h"

#include <stdlib.h>



Stack_element *create_stack_element(List_element **head ,FFree f) {
    
    Stack_element *stack =(Stack_element *)malloc(sizeof(Stack_element));
    if(stack == NULL){
        return NULL;
    } else {
        stack -> element = '\0';
        stack -> next = NULL;
        return stack;
    }
}


Stack_operation *create_stack_operation(List_operation **head ,FFree f) {

    Stack_operation *stack = (Stack_operation *)malloc(sizeof(Stack_operation));
    if(stack == NULL){
        return NULL;
    } else {
        stack -> operation = '\0' ;
        stack -> next = NULL;
        return stack;
    }
}


void stack_push_element (Stack_element **head, char elements) {

    Stack_element *value = (Stack_element *)malloc(sizeof(Stack_element));
    if (value == NULL){
        return;
    } else {
        value -> next = *head;
        value -> element = elements;
        *head = value;
    }
}


void stack_push_operation (Stack_operation **head, char operations) {

    Stack_operation *value = (Stack_operation *)malloc(sizeof(Stack_operation));
    if(value == NULL){
        return;
    } else {
        value -> next = *head;
        value -> operation = operations;
        *head = value;
    }
}


int stack_empty_operation(Stack_operation **head) {
    return (*head == NULL) ? 1 : 0;
}

Stack_operation *stack_peek_operation(Stack_operation **head) {

    if(*head != NULL){
        return *head;
    } else {
        return NULL;
    }
}


char stack_pop_operation (Stack_operation **head) {

    if(*head == NULL){
        return '\0';
    } else {
        Stack_operation *temp = *head;
        char operation = temp -> operation;
        *head = (*head) -> next;
        free(temp);
        return operation;
    }
}


char stack_pop_element (Stack_element **head) {

    if(*head == NULL){
        return '\0';
    } else {
        Stack_element *temp  = *head;
        char element = temp -> element;
        *head = (*head) -> next;
        free(temp);
        return element;
    }
}


void free_stack_element(Stack_element **head) {

    Stack_element *temp = *head;

    while(temp != NULL){
        Stack_element *next = temp -> next;
        free(temp);
        temp = next;
    }

    *head = NULL;
}



void free_stack_operation(Stack_operation **head) {

    Stack_operation *temp = *head;

    while(temp != NULL){
        Stack_operation *next = temp -> next;
        free(temp);
        temp = next;
    }

    *head = NULL;

}

/*Что бы избежать конфликта*/
Data stack_get(const Stack_element *stack){

    if(stack == NULL){
        return (Data){0};
    }
    return stack -> element;
}
