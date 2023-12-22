
// main.cpp
#include "array.h"
#include <iostream>
#include <ctime>

void processArray(Array* arr, int m, int n) {
    for (size_t i = 0; i < array_size(arr); i++) {
        if (array_get(arr, i) % 2 != 0) {
            array_set(arr, i, array_get(arr, i) - m);
        }
        if (i % 2 == 0) {
            array_set(arr, i, array_get(arr, i) + n);
        }
    }
}

void findMaxSum(const Array* arr) {
    if (array_size(arr) < 5) {
        std::cout << "������ ������� ��� ��� ���������� ������������ ����� ���� �������� ���������." << std::endl;
        return;
    }

    int currentSum = 0;

    // ��������� ��������� ����� ������ ���� ���������
    for (size_t i = 0; i < 5; i++) {
        currentSum += array_get(arr, i);
    }

    int maxSum = currentSum;

    // ���������� �� �������, �������� ����� �� ������ ��������
    for (size_t i = 5; i < array_size(arr); i++) {
        // ��������� ����� �������
        currentSum += array_get(arr, i);
        // ������� ����� ������ ������� (��, ��� �� ��������� "����������� ����")
        currentSum -= array_get(arr, i - 5);

        // ��������� ������������ ����� ��� �������������
        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
    }

    std::cout << "������������ ����� ���� �������� ���������: " << maxSum << std::endl;
}


void printArray(const Array* arr, const std::string& label) {
    std::cout << label << ": ";
    for (size_t i = 0; i < array_size(arr); i++) {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << std::endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    int size, m, n;
    std::cout << "������� ������ �������: ";
    std::cin >> size;
    Array* arr = array_create(size);

    // ���������� ������� ���������� �������
    for (size_t i = 0; i < array_size(arr); i++) {
        array_set(arr, i, rand() % 100); // ��������� ���������� ������� �� 0 �� 99
    }

    printArray(arr, "�������� ������");

    std::cout << "������� �������� m � n: ";
    std::cin >> m >> n;

    processArray(arr, m, n);
    printArray(arr, "������������ ������");

    findMaxSum(arr);

    array_delete(arr);

    return 0;
}