#include <iostream>
#include "array.h"

int main()
{
    int failed = 0;

    // 1. Создание и размер
    Array *arr = array_create(10);
    if (arr == nullptr || array_size(arr) != 10) {
        std::cout << "FAIL: create/size\n";
        ++failed;
    }

    // 2. Заполнение и чтение
    for (int i = 0; i < 10; ++i)
        array_set(arr, i, i * 2);

    for (int i = 0; i < 10; ++i)
        if (array_get(arr, i) != i * 2) {
            std::cout << "FAIL: set/get at " << i << "\n";
            ++failed;
            break;
        }

    // 3. Перезапись
    array_set(arr, 3, -100);
    if (array_get(arr, 3) != -100) {
        std::cout << "FAIL: overwrite\n";
        ++failed;
    }

    array_delete(arr);

    // 4. Выход за границы
    arr = array_create(3);
    array_set(arr, 0, 1);
    array_set(arr, 100, 999);
    if (array_get(arr, 0) != 1 || array_get(arr, 100) != 0) {
        std::cout << "FAIL: out of bounds\n";
        ++failed;
    }
    array_delete(arr);

    // 5. Нулевой размер
    arr = array_create(0);
    if (arr == nullptr || array_size(arr) != 0) {
        std::cout << "FAIL: zero size\n";
        ++failed;
    }
    array_delete(arr);
    if (array_size(nullptr) != 0 || array_get(nullptr, 0) != 0) {
        std::cout << "FAIL: nullptr\n";
        ++failed;
    }

    if (failed == 0)
        std::cout << "1";

    return failed == 0 ? 0 : 1;
}