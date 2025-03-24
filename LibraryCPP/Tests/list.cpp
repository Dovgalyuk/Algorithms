#include <iostream>
#include "list.h"

int main() {
    List* list = list_create();

    if (!list) {
        std::cout << "List creation error\n";
        return 1;
    }

    // Вставляем теги вместо чисел
    list_insert(list, "<html>");
    list_insert(list, "<body>");
    list_insert(list, "<h1>");

    if (list_item_data(list_first(list)) != "<h1>") {
        std::cout << "list_insert error\n";
        return 1;
    }

    list_insert_after(list, list_first(list), "<p>");

    if (list_item_data(list_item_next(list_first(list))) != "<p>") {
        std::cout << "list_insert_after error\n";
        return 1;
    }

    list_erase_first(list);

    if (list_item_data(list_first(list)) != "<p>") {
        std::cout << "list_erase error\n";
        return 1;
    }

    std::cout << "List: ";
    for (ListItem* item = list_first(list); item; item = list_item_next(item)) {
        std::cout << list_item_data(item) << " ";
    }
    std::cout << "\n";

    list_delete(list);
    return 0;
}