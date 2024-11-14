#include <iostream>
#include "list.h"

void free_element(void* ptr) {
}

struct List_element {
    Data element;
    struct List_element *next;
    FFree *distruct;
};
int check_list(List_element *head, char expected_order[], int size) {
    List_element *value = head;

    for (int i = 0; i < size; i++) {
        if (value == nullptr) {
            return 1;
        } else if (value -> element != expected_order[i]) {
            return 1;
        }
        value = value -> next;
    } if (value != nullptr) {
        return 1;
    }
    return 0;
}

int main(void) {
    List_element *head_1 = nullptr;

    if (create_list_element(&head_1, free_element) == nullptr) {
        std::cerr << "Failed to create list element" << std::endl;
        return 1;
    }

    add_list_element(&head_1, 'A');
    add_list_element(&head_1, 'B');
    add_list_element(&head_1, 'C');

    char expected_order[] = {'A', 'B', 'C'};
    int size = sizeof(expected_order) / sizeof(expected_order[0]);

    std::cout << "Expected order: ";
    for (int i = 0; i < size; i++) {
        std::cout << expected_order[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "List elements: ";
    List_element *temp = head_1;
    while (temp != nullptr) {
        std::cout << temp -> element << " ";
        temp = temp -> next;
    }
    std::cout << std::endl;

    /*if(check_list(head_1, expected_order, size)){
        std::cout << "Incorrect" << std::endl;
    } else {
        std::cout << "Correct" << std::endl;
    }*/

    delete_list_memory_element(&head_1);

    return 0;
}
