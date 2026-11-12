// Дополнительный тест списка №2: удаление элементов
#include <iostream>
#include "list.h"

int fail(const char *msg)
{
    std::cout << "Error: " << msg << "\n";
    return 1;
}

int main()
{
    List *list = list_create();

    // из пустого списка удалять нечего
    if (list_erase_first(list) != NULL)
        return fail("erase from empty list must return NULL");

    // делаем список 1 2 3
    ListItem *a = list_insert(list, 1);
    ListItem *b = list_insert_after(list, a, 2);
    ListItem *c = list_insert_after(list, b, 3);

    // удаляем из середины (2), должны получить указатель на 3
    if (list_erase_next(list, a) != c)
        return fail("erase_next in the middle");
    if (list_item_next(a) != c)
        return fail("list is broken after erase in the middle");

    // удаляем последний (3): вернётся NULL, last станет 1
    if (list_erase_next(list, a) != NULL)
        return fail("erase_next of last must return NULL");
    if (list_last(list) != a)
        return fail("last must move after erasing last element");

    // после последнего удалять нечего
    if (list_erase_next(list, a) != NULL)
        return fail("erase after last must return NULL");

    // удаляем единственный элемент: список пустой
    list_erase_first(list);
    if (list_first(list) != NULL || list_last(list) != NULL)
        return fail("list must be empty after erasing everything");

    // пустым списком можно пользоваться дальше
    list_insert(list, 7);
    if (list_item_data(list_first(list)) != 7 || list_item_data(list_last(list)) != 7)
        return fail("list must work after becoming empty");

    list_delete(list);

    std::cout << "List erase test passed\n";
    return 0;
}
