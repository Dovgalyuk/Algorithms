#include <iostream>
#include "list.h"

bool check_list(List& list, const int expected[], int size)
{
    auto item = list.first();

    for (int i = 0; i < size; ++i)
    {
        if (item == nullptr || item->data() != expected[i])
        {
            return false;
        }

        item = item->next();
    }

    if (item != nullptr)
    {
        return false;
    }

    if (size == 0)
    {
        return list.first() == nullptr && list.last() == nullptr;
    }

    auto last = list.last();

    return last != nullptr && last->data() == expected[size - 1];
}

int main()
{
    List list;

    if (list.first() != nullptr || list.last() != nullptr)
    {
        std::cout << "List creation error\n";
        return 1;
    }

    list.insert(1);
    list.insert(2);
    list.insert(3);

    const int expected1[] = { 3, 2, 1 };

    if (!check_list(list, expected1, 3))
    {
        std::cout << "list_insert error\n";
        return 1;
    }

    list = list;

    if (!check_list(list, expected1, 3))
    {
        std::cout << "list_assignment error\n";
        return 1;
    }

    list.insert_after(list.first(), 4);

    const int expected2[] = { 3, 4, 2, 1 };

    if (!check_list(list, expected2, 4))
    {
        std::cout << "list_insert_after error\n";
        return 1;
    }

    list.erase_first();

    const int expected3[] = { 4, 2, 1 };

    if (!check_list(list, expected3, 3))
    {
        std::cout << "list_erase_first error\n";
        return 1;
    }

    List copy(list);

    if (!check_list(copy, expected3, 3))
    {
        std::cout << "list_copy_constructor error\n";
        return 1;
    }

    List assigned;
    assigned.insert(100);
    assigned = list;

    if (!check_list(assigned, expected3, 3))
    {
        std::cout << "list_assignment error\n";
        return 1;
    }

    list.erase_next(nullptr);

    const int expected4[] = { 2, 1 };

    if (!check_list(list, expected4, 2))
    {
        std::cout << "list_erase_next error\n";
        return 1;
    }

    list.erase_first();
    list.erase_first();

    if (!check_list(list, nullptr, 0))
    {
        std::cout << "list_empty error\n";
        return 1;
    }

    std::cout << "List tests passed\n";
    return 0;
}