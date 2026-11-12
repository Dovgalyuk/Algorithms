#include <iostream>
#include "list.h"

bool checkList()
{
    List list;
    if (list.first() || list.last() || list.erase_first()) return false;
    List::Item *one = list.insert_after(nullptr, 1);
    List::Item *three = list.insert_after(one, 3);
    List::Item *two = list.insert_after(one, 2);
    if (one->prev() || three->next()) return false;
    if (one->next() != two || two->prev() != one) return false;
    if (two->next() != three || three->prev() != two) return false;
    if (list.last() != three) return false;

    List copy(list);
    List assigned;
    assigned.insert(99);
    assigned = list;
    list.erase_next(one);
    if (one->next() != three || three->prev() != one) return false;
    if (copy.first() == one || copy.first()->next()->data() != 2) return false;
    if (assigned.first()->next()->data() != 2) return false;
    if (list.erase_next(one) || list.last() != one) return false;
    if (one->next()) return false;
    if (list.erase_next(nullptr) || list.first() || list.last()) return false;

    int expected = 3;
    for (List::Item *item = copy.last(); item; item = item->prev())
    {
        if (item->data() != expected) return false;
        expected--;
    }
    if (expected != 0) return false;
    assigned = list;
    return assigned.first() == nullptr && assigned.last() == nullptr;
}
int main()
{
    if (!checkList()) return 1;
    List *list = new List;

    if (!list)
    {
        std::cout << "List creation error\n";
        return 1;
    }

    list->insert(1);
    list->insert(2);
    list->insert(3);

    *list = *list;

    if (list->first()->data() != 3)
    {
        std::cout << "list_insert error\n";
        return 1;
    }

    if (list->last()->data() != 1)
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

    List copy(*list);

    std::cout << "List: ";
    for (auto item = list->first() ; item ; item = item->next())
    {
        std::cout << item->data() << " ";
    }
    std::cout << "\n";

    delete list;
}
