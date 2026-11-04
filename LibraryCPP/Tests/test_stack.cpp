#include <iostream>
#include "vector.h"

// Печатает сообщение и завершает тест с ошибкой
#define CHECK(cond, msg)                         \
    if (!(cond))                                 \
    {                                            \
        std::cout << "FAILED: " << msg << "\n";  \
        vector_delete(vector);                   \
        return 1;                                \
    }

int main()
{
    Vector *vector = vector_create();

    // Новый вектор пустой
    CHECK(vector_size(vector) == 0, "new vector is not empty");

    // Увеличение размера, запись и чтение
    vector_resize(vector, 5);
    CHECK(vector_size(vector) == 5, "size after resize(5)");
    for (size_t i = 0; i < 5; ++i)
        vector_set(vector, i, (Data)(i * 10));
    for (size_t i = 0; i < 5; ++i)
        CHECK(vector_get(vector, i) == (Data)(i * 10), "get after set");

    // Перезапись элемента
    vector_set(vector, 2, -7);
    CHECK(vector_get(vector, 2) == -7, "overwrite element");

    // При увеличении старые элементы сохраняются
    vector_resize(vector, 100);
    CHECK(vector_size(vector) == 100, "size after resize(100)");
    CHECK(vector_get(vector, 0) == 0 && vector_get(vector, 1) == 10
        && vector_get(vector, 2) == -7 && vector_get(vector, 4) == 40,
        "old elements lost after growing");

    // При уменьшении начало вектора сохраняется
    vector_resize(vector, 3);
    CHECK(vector_size(vector) == 3, "size after resize(3)");
    CHECK(vector_get(vector, 1) == 10 && vector_get(vector, 2) == -7,
        "elements lost after shrinking");

    // Уменьшение до нуля и повторное использование
    vector_resize(vector, 0);
    CHECK(vector_size(vector) == 0, "size after resize(0)");
    vector_resize(vector, 1);
    vector_set(vector, 0, 42);
    CHECK(vector_get(vector, 0) == 42, "reuse after resize(0)");

    // Много добавлений по одному элементу (проверка скорости O(1) в среднем)
    const size_t N = 1000000;
    vector_resize(vector, 0);
    for (size_t i = 0; i < N; ++i)
    {
        vector_resize(vector, i + 1);
        vector_set(vector, i, (Data)i);
    }
    CHECK(vector_size(vector) == N, "size after many appends");
    for (size_t i = 0; i < N; ++i)
        CHECK(vector_get(vector, i) == (Data)i, "value after many appends");

    vector_delete(vector);
    std::cout << "vector: OK\n";
    return 0;
}