// Дополнительный тест списка №1: пустой список и вставка
#include <iostream>
#include "list.h"

// печатает ошибку и возвращает 1, чтобы тест упал
int fail(const char *msg)
{
    std::cout << "Error: " << msg << "\n";
    return 1;
}

int main()
{
    List *list = list_create();

    // пустой список: нет ни первого, ни последнего
    if (list_first(list) != NULL || list_last(list) != NULL)
        return fail("empty list must have no first/last");

    // один элемент: он и первый, и последний, следующего нет
    ListItem *one = list_insert(list, 10);
    if (list_first(list) != one || list_last(list) != one)
        return fail("single element must be first and last");
    if (list_item_next(one) != NULL)
        return fail("next of the only element must be NULL");

    // вставка после последнего меняет last
    ListItem *two = list_insert_after(list, one, 20);
    if (list_last(list) != two)
        return fail("insert_after last must update last");

    // insert_after с NULL вставляет в начало
    list_insert_after(list, NULL, 5);
    if (list_item_data(list_first(list)) != 5)
        return fail("insert_after(NULL) must insert first");

    // проверяем порядок 5 10 20 и что обход заканчивается
    // (кольцо замкнуто через фиктивный элемент, обход не должен зациклиться)
    int expected[3] = {5, 10, 20};
    int cnt = 0;
    for (ListItem *it = list_first(list); it; it = list_item_next(it))
    {
        if (cnt >= 3)
            return fail("iteration does not stop");
        if (list_item_data(it) != expected[cnt])
            return fail("wrong order of elements");
        cnt++;
    }
    if (cnt != 3)
        return fail("wrong number of elements");

    // удаляем непустой список (утечки поймает санитайзер)
    list_delete(list);

    std::cout << "List insert test passed\n";
    return 0;
}
