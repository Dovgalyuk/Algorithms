#include <iostream>
#include "list.h"

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

void delete_element_test(List_element **head);
void delete_operation_test(List_operation **head);

void add_element(List_element **head, Data x);
void add_operation(List_operation **head, Data x);

void  print_list_element(List_element **head);
void  print_list_operation(List_operation **head);

int main(void){

    List_element *head_1 = NULL;
    List_operation *head_2 = NULL;

    create_list_element(&head_1,free);
    create_list_operation(&head_2,free);

    add_element(&head_1, Data('A'));
    add_element(&head_1, Data('B'));
    add_operation(&head_2,Data('1'));
    add_operation(&head_2,Data('2'));


    std::cout << "List_elements:";
    print_list_element(&head_1);
    std::cout << "List_operation";
    print_list_operation(&head_2);

    delete_element_test(&head_1);
    delete_operation_test(&head_2);

    return 0;
}


void add_element(List_element **head, Data x){

    List_element *new_element = new List_element;
    if(new_element != nullptr){
        new_element -> element = x;
        new_element -> next = *head;
        *head = new_element;
    }
}


void add_operation(List_operation **head, Data x){

    List_operation *new_operation = new List_operation;
    if(new_operation != nullptr){
        new_operation -> operation = x;
        new_operation -> next = *head;
        *head = new_operation;
    }
}


void  print_list_element(List_element **head){

    List_element *temp = *head;

    while(temp != NULL){
        std::cout << temp -> element << " ";
        temp = temp -> next;
    }
    std::cout << std::endl;
}


void  print_list_operation(List_operation **head){

    List_operation *temp = *head;

    while(temp != NULL){
        std::cout << temp -> operation << " ";
        temp = temp -> next;
    }
    std::cout << std::endl;
}


void delete_element_test(List_element **head){
    while(*head != NULL){
        List_element *temp = *head;
        *head = (*head) -> next;
        delete temp;
    }
}

void delete_operation_test(List_operation **head){
    while(*head != NULL){
        List_operation *temp = *head;
        *head = (*head) -> next;
        delete temp;
    }
}
