#include "vector.h"
#include <iostream>
using namespace std;

int main() {
    Vector v;

    // Тест 1: пустой вектор
    if (v.size() != 0) {
        cout << "FAIL: empty vector size != 0\n";
        return 1;
    }

    // Тест 2: push_back
    v.push_back("A");
    v.push_back("B");
    v.push_back("C");
    if (v.size() != 3) {
        cout << "FAIL: size != 3\n";
        return 1;
    }

    // Тест 3: get
    if (v.get(0) != "A" || v.get(1) != "B" || v.get(2) != "C") {
        cout << "FAIL: get wrong values\n";
        return 1;
    }

    // Тест 4: set
    v.set(1, "X");
    if (v.get(1) != "X") {
        cout << "FAIL: set wrong value\n";
        return 1;
    }

    // Тест 5: resize (увеличение)
    v.resize(5);
    if (v.size() != 5) {
        cout << "FAIL: resize up failed\n";
        return 1;
    }

    // Тест 6: resize (уменьшение)
    v.resize(2);
    if (v.size() != 2) {
        cout << "FAIL: resize down failed\n";
        return 1;
    }

    // Тест 7: копирование
    Vector copy = v;
    if (copy.size() != 2 || copy.get(0) != "A") {
        cout << "FAIL: copy failed\n";
        return 1;
    }

    // Тест 8: оператор присваивания
    Vector other;
    other = v;
    if (other.size() != 2 || other.get(0) != "A") {
        cout << "FAIL: assignment failed\n";
        return 1;
    }

    // Тест 9: reverse — чётное число элементов
    Vector rev1;
    rev1.push_back("A");
    rev1.push_back("B");
    rev1.push_back("C");
    rev1.push_back("D");
    rev1.reverse();
    if (rev1.get(0) != "D" || rev1.get(1) != "C" ||
        rev1.get(2) != "B" || rev1.get(3) != "A") {
        cout << "FAIL: reverse (even) wrong\n";
    return 1;
        }

    // Тест 10: reverse — нечётное число элементов
    Vector rev2;
    rev2.push_back("1");
    rev2.push_back("2");
    rev2.push_back("3");
    rev2.reverse();
    if (rev2.get(0) != "3" || rev2.get(1) != "2" || rev2.get(2) != "1") {
        cout << "FAIL: reverse (odd) wrong\n";
        return 1;
    }

    // Тест 11: reverse — один элемент (ничего не меняется)
    Vector rev3;
    rev3.push_back("X");
    rev3.reverse();
    if (rev3.get(0) != "X") {
        cout << "FAIL: reverse (single) wrong\n";
        return 1;
    }

    // Тест 12: reverse — пустой вектор (не должен падать)
    Vector rev4;
    rev4.reverse();
    if (rev4.size() != 0) {
        cout << "FAIL: reverse (empty) broke size\n";
        return 1;
    }

    // Тест 13: reverse — дважды = исходный порядок
    Vector rev5;
    rev5.push_back("A");
    rev5.push_back("B");
    rev5.push_back("C");
    rev5.reverse();
    rev5.reverse();
    if (rev5.get(0) != "A" || rev5.get(1) != "B" || rev5.get(2) != "C") {
        cout << "FAIL: reverse twice != original\n";
        return 1;
    }

    cout << "All Vector tests passed\n";
    return 0;
}
