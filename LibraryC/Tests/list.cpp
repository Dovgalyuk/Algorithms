#include <iostream>
#include "list.h"

struct List_element {
    Data element;
    struct List_element *next;
    FFree *distruct;
};


void delete_element_test(List_element **head);


void add_element(List_element **head, Data x);


void print_list_element(List_element **head);


int main(void){
    List_element *head_1 = nullptr;


    add_element(&head_1, Data('A'));
    add_element(&head_1, Data('B'));

    std::cout << "List_elements: ";
    print_list_element(&head_1);

    delete_element_test(&head_1);

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


void print_list_element(List_element **head){
    List_element *temp = *head;
    while(temp != nullptr){
        std::cout << temp->element << " ";
        temp = temp -> next;
    }
    std::cout << '\n';
}


void delete_element_test(List_element **head){
    while(*head != nullptr){
        List_element *temp = *head;
        *head = (*head) -> next;
        delete temp;
    }
}



