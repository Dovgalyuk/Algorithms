#include <iostream>
#include "../LibraryCPP/list.h"
#include "../LibraryCPP/stack.h"

void list_print(const List *list);

int main () {
    List* list = list_create();
    Stack* stack = stack_create();
    stack->list->tail;

    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        list_insert(list, num);
    }

    list_print(list);

    list_delete(list);

    return 0;
}