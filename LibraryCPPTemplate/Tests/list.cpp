#include <iostream>
#include "list.h"

// Определяем тип MyList как List<int>
typedef List<int> MyList;

int main()
{
    // Создаем новый объект типа MyList
    MyList* list = new MyList;

    // Проверяем, был ли создан объект успешно
    if (!list)
    {
        std::cout << "List creation error\n";
        return 1;
    }

    // Добавляем элементы в список
    list->insert(1);
    list->insert(2);
    list->insert(3);

    // Проверяем первый элемент
    if (list->first()->data() != 3)
    {
        std::cout << "list_insert error\n";
        delete list;
        return 1;
    }

    // Вставка элемента после первого элемента
    list->insert_after(list->first(), 4);

    // Проверяем второй элемент
    if (list->first()->next()->data() != 4)
    {
        std::cout << "list_insert_after error\n";
        delete list;
        return 1;
    }

    // Удаляем первый элемент
    list->erase_first();

    // Проверяем после удаления первого элемента
    if (list->first()->data() != 4)
    {
        std::cout << "list_erase error\n";
        delete list;
        return 1;
    }

    // Создаем копию списка
    MyList copy(*list);

    // Выводим содержимое списка
    std::cout << "List: ";
    for (auto item = list->first(); item != nullptr; item = item->next())
    {
        std::cout << item->data() << " ";
    }
    std::cout << "\n";

    // Удаляем динамически выделенную память
    delete list;
}
