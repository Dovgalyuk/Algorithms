#include <iostream>
#include <vector>

#include "customPriorityQueue.h"

// Компаратор для Min-Heap (меньшее число = выше приоритет)
struct IntLess {
    bool operator()(int a, int b) const {
        return a < b;
    }
};

int main() {
    CustomPriorityQueue<int, IntLess> pq;

    // Проверка на инициализацию
    if (!pq.empty() || pq.size() != 0) {
        std::cout << "Initialization failed: queue should empty\n";
        return 1;
    }

    // Проверка на добавление элементов
    pq.push(30);
    pq.push(10);
    pq.push(20);
    if (pq.size() != 3) {
        std::cout << "Push failed: size incorrect\n";
        return 1;
    }

    // Проверка на логику работы
    if (pq.top() != 10) {
        std::cout << "Priority logic failed: expected 10, but is " << pq.top() << "\n";
        return 1;
    }
    pq.pop();
    if (pq.top() != 20) {
        std::cout << "Priority logic failed: expected 20, but is " << pq.top() << "\n";
        return 1;
    }
    pq.pop();
    if (pq.top() != 30) {
        std::cout << "Priority logic failed: expected 30, but is " << pq.top() << "\n";
        return 1;
    }
    pq.pop();

    // Проверка на пустоту после удаления елементов
    if (!pq.empty()) {
        std::cout << "Pop failed: queue is not empty\n";
        return 1;
    }

    std::cout << "Queue tests passed\n";
    return 0;
}
