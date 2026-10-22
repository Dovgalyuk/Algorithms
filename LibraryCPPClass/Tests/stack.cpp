#include "stack.h"
#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    Stack stack;

    // Тест 1: пустой стек
    if (!stack.empty()) {
        cout << "FAIL: empty stack not empty\n";
        return 1;
    }

    // Тест 2: get на пустом стеке бросает исключение
    try {
        stack.get();
        cout << "FAIL: get on empty didn't throw\n";
        return 1;
    } catch (const out_of_range&) {
        // ожидаемо
    }

    // Тест 3: pop на пустом стеке бросает исключение
    try {
        stack.pop();
        cout << "FAIL: pop on empty didn't throw\n";
        return 1;
    } catch (const out_of_range&) {
        // ожидаемо
    }

    // Тест 4: push
    stack.push("1");
    stack.push("2");
    stack.push("3");
    if (stack.empty()) {
        cout << "FAIL: stack empty after push\n";
        return 1;
    }

    // Тест 5: get (LIFO)
    if (stack.get() != "3") {
        cout << "FAIL: get != 3\n";
        return 1;
    }

    // Тест 6: pop
    stack.pop();
    if (stack.get() != "2") {
        cout << "FAIL: after pop get != 2\n";
        return 1;
    }

    // Тест 7: ещё pop
    stack.pop();
    if (stack.get() != "1") {
        cout << "FAIL: after second pop get != 1\n";
        return 1;
    }

    // Тест 8: полная очистка
    stack.pop();
    if (!stack.empty()) {
        cout << "FAIL: stack not empty after pops\n";
        return 1;
    }

    // Тест 9: push после очистки
    stack.push("4");
    stack.push("5");
    if (stack.get() != "5") {
        cout << "FAIL: after re-push get != 5\n";
        return 1;
    }

    // Тест 10: копирование стека
    Stack copy = stack;
    if (copy.get() != "5") {
        cout << "FAIL: copy failed\n";
        return 1;
    }
    copy.pop();
    if (copy.get() != "4") {
        cout << "FAIL: copy failed (after pop)\n";
        return 1;
    }

    // Тест 11: оператор присваивания
    Stack other;
    other = stack;
    if (other.get() != "5") {
        cout << "FAIL: assignment failed\n";
        return 1;
    }

    cout << "All Stack tests passed\n";
    return 0;
}
