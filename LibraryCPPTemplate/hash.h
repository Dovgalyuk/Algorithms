#pragma once

#include <iostream>
#include <string>
#include "array.h"
#include <utility> // Для использования std::pair

// Класс HashTable для реализации хеш-таблицы
class HashTable {
public:
    // Внутренняя структура для хранения элементов таблицы
    struct Element {
        std::string key;     // Ключ
        std::string value;   // Значение
        bool deleted;        // Флаг удаленного элемента
        // Конструктор по умолчанию
        Element() : key(""), value(""), deleted(false) {}
        // Конструктор с параметрами
        Element(std::string key, std::string value, bool deleted = false) : key(key), value(value), deleted(deleted) {}
    };

private:
    Array<Element>* elements; // Массив элементов хеш-таблицы
    int capacity;             // Вместимость таблицы
    int size;                 // Текущее количество элементов
    int count_deleted = 0;    // Счетчик удаленных элементов

    // Первая хеш-функция (индекс)
    static int FirstHashFunction(const std::string& key, int capa) {
        // Инициализация переменной hash, которая будет использоваться для накопления хеш-значения.
        int hash = 0;
        unsigned long long unique_value = 1;

        // Цикл проходит по каждому символу в строке key.
        for (size_t i = 0; key[i]; i++) {
            // Для каждого символа ключа вычисляется хеш-значение.
            // Каждый символ влияет на конечное значение хеша,
            // которое затем берется по модулю вместимости хеш-таблицы (capa),
            // чтобы гарантировать, что хеш будет в пределах размера массива.
            hash = (hash * unique_value + key[i]) % capa;
        }
        return hash % capa;
    }

    // Вторая хеш-функция (индекс с обновленными параметрами уникального значения)
    static int SecondHashFunction(const std::string& key, int capa) {
        // Инициализация хеш-значения нулем.
        int hash = 0;

        // Начальное уникальное значение множителя равно 1. В этой функции это значение важно,
        // поскольку оно изменяется в каждой итерации, в отличие от FirstHashFunction.
        unsigned long long unique_value = 1;

        // Проходим по каждому символу ключа.
        for (size_t i = 0; key[i]; i++) {
            // Вычисляем хеш-значение, комбинируя текущий хеш, ASCII значение символа
            // и текущее уникальное значение множителя. Операция модуля гарантирует, что хеш находится
            // в пределах размера таблицы.
            hash = (hash * unique_value + key[i]) % capa;

            // Число 27 выбрано не случайно, обычно оно должно быть простым числом,
            // чтобы помочь обеспечить хорошее распределение хеш-значений.
            unique_value *= 27;
        }

        // Вычисляем окончательное хеш-значение по модулю вместимости таблицы, чтобы убедиться, что оно в пределах допустимых границ.
        int result = hash % capa;

        // Чтобы гарантировать, что шаг в схеме двойного хеширования не равен нулю и не является кратным размеру таблицы,
        // что важно для обеспечения пробирования всех слотов таблицы, результат корректируется, чтобы быть нечетным.
        // Если результат четный, добавляем 1, чтобы сделать его нечетным. Таким образом, вторая хеш-функция никогда не вернет ноль
        // (что привело бы к отсутствию движения в последовательности пробирования) и обеспечит лучшее распределение проб.
        if (result % 2 == 0) return result + 1;
        return result;
    }

    // Проверка необходимости ресайза
    bool check_capacity() {
        return this->size + this->count_deleted >= this->capacity / 2;
    }

    //// Алгоритм для определения индекса элемента в хеш-таблице
    //static int algorithm(const std::string& key, Array<Element>* in_elements, int capa, bool& not_found) {
    //    // Используем первую хеш-функцию для определения начального индекса элемента
    //    int first_hash = FirstHashFunction(key, capa);
    //    int final_hash = first_hash;

    //    // Если начальная позиция занята и элемент не помечен как удалённый, проверяем её
    //    if (!in_elements->get(final_hash)->key.empty() && !in_elements->get(final_hash)->deleted) {
    //        // Если мы ищем элемент и он присутствует по этому индексу, сбрасываем not_found и возвращаем индекс
    //        if (not_found && (key == in_elements->get(final_hash)->key)) {
    //            not_found = false;
    //            return final_hash;
    //        }

    //        // Рассчитываем индекс с помощью второй хеш-функции для разрешения коллизий
    //        int second_hash = SecondHashFunction(key, capa);

    //        // Начинаем итеративный процесс для нахождения нового индекса
    //        int iter = 1;

    //        // Применяем двойное хеширование для нахождения свободного индекса или индекса с искомым ключом
    //        final_hash = (first_hash + iter * second_hash) % capa;

    //        // Повторяем до тех пор, пока не найдём свободный индекс или индекс с ключом
    //        while (!in_elements->get(final_hash)->key.empty() && !in_elements->get(final_hash)->deleted) {
    //            // Если нашли индекс с искомым ключом и мы в режиме поиска, сбрасываем not_found и возвращаем индекс
    //            if (not_found && key == in_elements->get(final_hash)->key) {
    //                not_found = false;
    //                return final_hash;
    //            }
    //            // Увеличиваем итератор и ищем следующий индекс
    //            iter++;
    //            final_hash = (first_hash + iter * second_hash) % capa;
    //        }
    //    }
    //    // Возвращаем индекс, куда можно поместить новый элемент или где находится элемент с искомым ключом
    //    return final_hash;
    //}

    // Алгоритм для определения индекса элемента в хеш-таблице
    static int algorithm(const std::string& key, Array<Element>* in_elements, int capa, bool& not_found) {
        // Вычисляем начальный индекс с помощью первой хеш-функции
        int first_hash = FirstHashFunction(key, capa);
        // Вычисляем шаг для двойного хеширования с помощью второй хеш-функции
        int second_hash = SecondHashFunction(key, capa);

        // Итератор для обхода хеш-таблицы при коллизиях
        int iter = 0;
        // Индекс первого встреченного удаленного элемента, инициализирован -1 (отсутствие такого элемента)
        int first_deleted_index = -1;

        // Цикл, который продолжается до нахождения подходящего индекса
        while (true) {
            // Вычисляем индекс, используя двойное хеширование
            int final_hash = (first_hash + iter * second_hash) % capa;
            // Получаем элемент по вычисленному индексу
            Element* elem = in_elements->get(final_hash);

            // Если элемент удален и мы еще не записали индекс удаленного элемента
            if (elem->deleted && first_deleted_index == -1) {
                first_deleted_index = final_hash;
            }

            // Если нашли пустую ячейку или ячейку с искомым ключом
            if (elem->key.empty() || elem->key == key) {
                // Если ключ не найден и есть индекс удаленного элемента, возвращаем его индекс
                if (elem->key.empty() && first_deleted_index != -1 && not_found) {
                    return first_deleted_index;
                }

                // Устанавливаем флаг not_found в зависимости от того, пустая ли ячейка
                not_found = elem->key.empty();
                return final_hash;
            }

            // Увеличиваем итератор для следующего шага в пробировании
            iter++;
        }
    }

    // Функция расширения таблицы
    void resize() {
        // Сохраняем старую вместимость таблицы.
        int old_capacity = this->capacity;

        // Увеличиваем вместимость таблицы в четыре раза.
        this->capacity *= 4;

        // Создаем новый массив элементов с новой вместимостью.
        Array<Element>* new_elements = new Array<Element>(this->capacity);

        // Перебираем элементы старого массива.
        for (int i = 0; i < old_capacity; ++i) {
            // Получаем элемент по индексу.
            Element* elem = this->elements->get(i);
            // Если элемент не пустой и не был удален...
            if (!elem->key.empty() && !elem->deleted) {
                // Устанавливаем флаг not_found в истину, что указывает на то, что мы добавляем элемент, а не ищем его.
                bool not_found = true;
                // Находим новый индекс для элемента в новом массиве с помощью алгоритма двойного хеширования.
                int index = algorithm(elem->key, new_elements, this->capacity, not_found);
                // Вставляем элемент в новую позицию.
                new_elements->set(index, *elem);
            }
        }

        // Удаляем старый массив элементов.
        delete this->elements;
        // Назначаем новый массив элементов текущим.
        this->elements = new_elements;
        // Обнуляем счетчик удаленных элементов, так как они не переносятся в новую таблицу.
        this->count_deleted = 0;
    }

    // Поиск индекса элемента по ключу
    int find_index(const std::string& key) {
        // Инициализируем флаг, который будет указывать, найден ли элемент.
        bool not_found = true;

        // Применяем алгоритм двойного хеширования для определения индекса элемента.
        // Этот алгоритм учитывает возможные коллизии и позволяет найти индекс,
        // где должен находиться элемент с данным ключом, если он существует.
        int hash_index = algorithm(key, this->elements, this->capacity, not_found);

        // Проверяем, не был ли элемент помечен как не найденный в результате работы алгоритма.
        // Также проверяем, не был ли элемент с этим индексом помечен как удаленный.
        // Если элемент не найден или помечен как удаленный, возвращаем -1, что указывает на отсутствие элемента.
        if (not_found || this->elements->get(hash_index)->deleted) return -1;

        // Если элемент найден и он не помечен как удаленный, возвращаем его индекс.
        return hash_index;
    }

public:
    // Конструктор по умолчанию
    HashTable()
        : elements(new Array<Element>(16)), capacity(16), size(0), count_deleted(0) {}

    // Конструктор копирования
    HashTable(const HashTable& other)
        : elements(new Array<Element>(other.capacity)), capacity(other.capacity), size(other.size), count_deleted(other.count_deleted) {
        // Копирование элементов
        for (int i = 0; i < capacity; ++i) {
            Element* elem = other.elements->get(i);
            if (!elem->key.empty()) {
                elements->set(i, *elem);
            }
        }
    }

    // Оператор присваивания
    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            delete elements;

            capacity = other.capacity;
            size = other.size;
            count_deleted = other.count_deleted;
            elements = new Array<Element>(capacity);

            for (int i = 0; i < capacity; ++i) {
                Element* elem = other.elements->get(i);
                if (!elem->key.empty()) {
                    elements->set(i, *elem);
                }
            }
        }
        return *this;
    }

    // Деструктор
    ~HashTable() {
        delete elements;
    }

    // Добавление элемента
    void add(const std::string& key, const std::string& value) {
        // Флаг, указывающий на то, что позиция для вставки еще не найдена.
        bool not_found = true;

        // Вычисляем хеш-позицию для ключа с помощью алгоритма двойного хеширования.
        int final_hash = algorithm(key, this->elements, this->capacity, not_found);

        // Вставляем новый элемент с полученным хешем в массив elements.
        // Элемент создается на месте с использованием конструктора Element.
        elements->set(final_hash, Element(key, value));

        // Увеличиваем размер хеш-таблицы (количество хранимых элементов).
        this->size++;

        // Проверяем, не превышает ли сумма текущего размера и количества удаленных элементов половины вместимости.
        // Если это так, то необходимо увеличить размер хеш-таблицы для поддержания эффективности операций.
        if (check_capacity()) {
            // Вызываем метод resize для увеличения вместимости хеш-таблицы и перехеширования элементов.
            resize();
        }
    }

    // Удаление элемента
    void del(const std::string& key) {
        // Ищем индекс элемента, который соответствует ключу.
        // find_index возвращает -1, если элемент не найден.
        int index_to_delete = find_index(key);

        // Если индекс не был найден, то элемента с таким ключом нет в таблице,
        // и мы просто выходим из функции.
        if (index_to_delete == -1) return;

        // Если элемент найден, мы устанавливаем его статус как "удаленный".
        // Здесь не происходит физическое удаление элемента из массива,
        // мы лишь помечаем его как удаленный, изменяя флаг 'deleted' на true.
        this->elements->get(index_to_delete)->deleted = true;

        // Увеличиваем счетчик удаленных элементов.
        // Это значение используется в функции check_capacity для определения,
        // когда может потребоваться расширение таблицы.
        this->count_deleted++;
    }

    // Поиск элемента
    std::pair<bool, std::string> find(const std::string& key) {
        // Вызываем метод find_index для получения индекса элемента по ключу.
        int index = find_index(key);

        // Если find_index возвращает -1, элемент с таким ключом не найден или удален.
        // В этом случае возвращаем пару, первый элемент которой - false, второй - пустая строка.
        if (index == -1) return std::make_pair(false, "");

        // Если элемент найден, возвращаем пару, где первый элемент - true,
        // а второй - значение, связанное с ключом.
        return std::make_pair(true, elements->get(index)->value);
    }
};