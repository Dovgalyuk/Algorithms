#ifndef CUSTOM_PRIORITY_QUEUE_TEMPLATE_H
#define CUSTOM_PRIORITY_QUEUE_TEMPLATE_H

#include <vector>
#include <algorithm>

// Шаблонный класс очереди с приоритетами
// T - тип хранимых данных
// Compare - функтор для сравнения элементов
template <typename T, typename Compare> class CustomPriorityQueue {
public:
    // Конструкторы
    CustomPriorityQueue() = default;
    explicit CustomPriorityQueue(const Compare& comparator) : _cmp(comparator) {}

    // Проверка пустоты очереди
    bool empty() const {
        return _data.empty();
    }

    // Возвращает количество элементов в очереди
    size_t size() const {
        return _data.size();
    }

    // Добавляет элемент в очередь и восстанавливает свойства кучи
    void push(const T& value) {
        _data.push_back(value);
        sift_up(_data.size() - 1);
    }

    // Удаляет элемент с наивысшим приоритетом
    void pop() {
        if (_data.empty()) return;

        _data[0] = _data.back();
        _data.pop_back();

        if (!_data.empty()) {
            sift_down(0);
        }
    }

    // Возвращает элемент с наивысшим приоритетом
    T top() const { return !_data.empty() ? _data[0] : T(); }

private:
    std::vector<T> _data;
    Compare _cmp;

    // Просеивание элемента вверх
    void sift_up(size_t index) {
        while (index > 0) {
            size_t parent = (index - 1) / 2;

            if (_cmp(_data[index], _data[parent])) {
                std::swap(_data[index], _data[parent]);
                index = parent;
            }
            else {
                break;
            }
        }
    }

    // Просеивание элемента вниз
    void sift_down(size_t index) {
        size_t size = _data.size();
        while (true) {
            size_t left = 2 * index + 1;
            size_t right = 2 * index + 2;
            size_t small = index;

            if (left < size && _cmp(_data[left], _data[small])) {
                small = left;
            }

            if (right < size && _cmp(_data[right], _data[small])) {
                small = right;
            }

            if (small != index) {
                std::swap(_data[index], _data[small]);
                index = small;
            }
            else {
                break;
            }
        }
    }
};

#endif