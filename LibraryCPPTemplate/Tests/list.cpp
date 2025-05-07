#include <iostream>
#include "list.h"

typedef List<int> MyList;

int main()
{
    MyList *list = new MyList;

    if (!list)
    {
        std::cout << "List creation error\n";
        return 1;
    }

    list->insert(1);
    list->insert(2);
    list->insert(3);

    if (list->head->data() != 3)
{
    std::cout << "list_insert error\n";
    return 1;
}

list->insert_after(list->head, 4);

if (list->head->next()->data() != 4)
{
    std::cout << "list_insert_after error\n";
    return 1;
}

list->erase_first();

if (list->head->data() != 4)
{
    std::cout << "list_erase error\n";
    return 1;
}

MyList copy(*list);

std::cout << "List: ";
for (auto* it = list->head; it != nullptr; it = it->next())
{
    std::cout << it->data() << " ";
}
std::cout << "\n";

    delete list;
}
