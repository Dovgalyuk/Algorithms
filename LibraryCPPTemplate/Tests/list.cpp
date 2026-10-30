#include <iostream>
#include "list.h"

int main()
{
    List<int> list;
    if (!list.empty() || list.size() != 0)
        return 1;

    auto* one = list.insert(1);
    list.insert(2);
    list.insert(3);
    if (list.size() != 3 || list.first()->data() != 3 || list.last()->data() != 1)
        return 1;

    list.insert_after(one, 4);
    if (list.last()->data() != 4 || one->next()->data() != 4)
        return 1;

    list.erase_next(one);
    if (list.last()->data() != 1 || list.size() != 3)
        return 1;

    List<int> copy(list);
    copy.erase_first();
    if (copy.first()->data() != 2 || list.first()->data() != 3)
        return 1;

    list = list;
    if (list.size() != 3 || list.first()->data() != 3)
        return 1;

    list.clear();
    if (!list.empty() || list.first() != nullptr || list.last() != nullptr)
        return 1;

    std::cout << "List tests passed\n";
    return 0;
}
