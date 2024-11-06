#include <iostream>
#include "list.h"

void print_list(List* list) {
    for (auto item = list->first(); item; item = item->next()) {
        std::cout << item->data() << " ";
    }
    std::cout << "\n";
}

int main()
{
    List *list = new List;

    if (!list)
    {
        std::cout << "List creation error\n";
        return 1;
    }

    list->insert(1);
    list->insert(2);
    list->insert(3);

    if (list->first()->data() != 3)
    {
        std::cout << "list_insert error\n";
        return 1;
    }

    list->insert_after(list->first(), 4);

    if (list->first()->next()->data() != 4)
    {
        std::cout << "list_insert_after error\n";
        return 1;
    }

    list->erase_first();

    if (list->first()->data() != 4)
    {
        std::cout << "list_erase error\n";
        return 1;
    }

    std::cout << "List before erase_next: ";
    print_list(list);

    list->insert(5);
    list->insert_after(list->first()->next(), 6);

    if (list->first()->next()->next()->data() != 6)
    {
        std::cout << "list_insert_after multiple error\n";
        return 1;
    }

    std::cout << "List before erase_next: ";
    print_list(list);

    auto item_to_erase = list->first()->next();
    auto erased_item = list->erase_next(item_to_erase);

    if (erased_item->data() != 2)
    {
        std::cout << "list_erase_next error: expected next data to be 2\n";
        return 1;
    }

    std::cout << "List after erase_next: ";
    print_list(list);

    list->clear();
    if (list->first() != nullptr)
    {
        std::cout << "list_clear error\n";
        return 1;
    }

    list->insert(7);
    if (list->first()->data() != 7)
    {
        std::cout << "Error: push after empty list\n";
        return 1;
    }

    delete list;

    return 0;
}
