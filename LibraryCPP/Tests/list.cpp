#include <iostream>
#include "list.h"

int main() {
    List* list = list_create();

    if (!list) {
        std::cout << "List creation error\n";
        return 1;
    }

    // Вставляем элементы 1, 2, 3 в конец списка.
    list_insert(list, 1);
    list_insert(list, 2);
    list_insert(list, 3);

    // Проверяем первый элемент (он должен быть 1).
    if (list_item_data(list_first(list)) != 1) {
        std::cout << "list_insert error: incorrect first element\n";
        return 1;
    }

    // Вставляем 4 после первого элемента (1).
    list_insert_after(list, list_first(list), 4);

    // Проверяем, что следующий элемент после первого - 4.
    if (list_item_data(list_item_next(list_first(list))) != 4) {
        std::cout << "list_insert_after error: incorrect next element\n";
        return 1;
    }

    // Удаляем первый элемент (1).
    list_erase_first(list);

    // Проверяем, что первый элемент теперь 4 (первый следующий после старого 1).
    if (list_item_data(list_first(list)) != 4) {
        std::cout << "list_erase error: incorrect first element after erase\n";
        return 1;
    }

    // Печатаем список.
    std::cout << "List: ";
    ListItem* first = list_first(list);
    if (first) {
        ListItem* current = first;
        do {
            std::cout << list_item_data(current) << " ";
            current = list_item_next(current);
        } while (current != first);
    }
    std::cout << "\n";

    // Удаляем список.
    list_delete(list);
    std::cout << "Test completed successfully.\n";

    return 0;
}