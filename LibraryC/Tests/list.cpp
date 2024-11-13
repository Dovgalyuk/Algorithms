#include <iostream>
#include "list.h"

void free_element(void* ptr) {
}

struct List_element {
    Data element;
    struct List_element *next;
    FFree *distruct;
};

int main(void) {
    List_element *head_1 = nullptr;

    if (create_list_element(&head_1, free_element) == nullptr) {
        std::cerr << "Failed to create list element" << std::endl;
        return 1;
    }

    add_list_element(&head_1, 'A');
    add_list_element(&head_1, 'B');

    std::cout << "List elements: ";
    List_element *temp = head_1;
    while (temp != nullptr) {
        std::cout << temp->element << " ";
        temp = temp->next;
    }
    std::cout << std::endl;

    delete_list_memory_element(&head_1);

    return 0;
}
