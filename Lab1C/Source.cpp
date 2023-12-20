// array.h
#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

struct Array {
    int* data;
    size_t size;
};

Array array_create(size_t size);


// array.cpp
#include "array.h"
#include <cstdlib>

Array array_create(size_t size) {
    Array arr;
    arr.size = size;
    arr.data = new int[size];
    return arr;
}

void array_set(Array& arr, size_t index, int value) {
    if (index < arr.size) {
        arr.data[index] = value;
    }
}



// main.cpp
#include "array.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void processArray(Array& arr, int m, int n) {
    for (size_t i = 0; i < arr.size; i++) {
        if (arr.data[i] % 2 != 0) {
            arr.data[i] -= m;
        }
        if (i % 2 == 0) {
            arr.data[i] += n;
        }
    }
}

void findMaxSum(const Array& arr) {
    if (arr.size < 5) {
        std::cout << "������ ������� ��� ��� ���������� ������������ ����� ���� �������� ���������." << std::endl;
        return;
    }

    int currentSum = 0;

    // ��������� ��������� ����� ������ ���� ���������
    for (size_t i = 0; i < 5; i++) {
        currentSum += arr.data[i];
    }

    int maxSum = currentSum;

    // ���������� �� �������, �������� ����� �� ������ ��������
    for (size_t i = 5; i < arr.size; i++) {
        // ��������� ����� �������
        currentSum += arr.data[i];
        // ������� ����� ������ ������� (��, ��� �� ��������� "����������� ����")
        currentSum -= arr.data[i - 5];

        // ��������� ������������ ����� ��� �������������
        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
    }

    std::cout << "������������ ����� ���� �������� ���������: " << maxSum << std::endl;
}


void printArray(const Array& arr, const std::string& label) {
    std::cout << label << ": ";
    for (size_t i = 0; i < arr.size; i++) {
        std::cout << arr.data[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    int size, m, n;
    std::cout << "������� ������ �������: ";
    std::cin >> size;
    Array arr = array_create(size);

    // ���������� ������� ���������� �������
    for (size_t i = 0; i < arr.size; i++) {
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
