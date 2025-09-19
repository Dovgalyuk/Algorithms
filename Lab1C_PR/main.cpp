#include <iostream>
#include <fstream> // ��� ������.
#include <vector> // ��� vector.
#include <climits> // ��� INT_MIN.
#include "array.h"

using namespace std;

// ������� ��� ������ �� �����.

bool readFile(const string& filename, int& n, int*& data) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "������: ���� �� ������!" << endl;
        return false;
    }

    file >> n;
    if (n <= 0) {
        cout << "������: ������ <= 0!" << endl;
        return false;
    }

    data = new int[n];
    for (int i = 0; i < n; i++) {
        file >> data[i];
    }

    file.close();
    return true;
}

// ������� 4.

void task4(const string& filename) {
    int n = 0;
    int* data = nullptr;
    if (!readFile(filename, n, data)) {
        return;
    }

    Array arr(n);
    arr.fillFrom(data);

    int sum = 0;
    for (int i = 0; i < arr.getSize(); i++) {
        sum += arr.get(i);
    }

    int count = 0;
    vector<int> indices;
    for (int i = 0; i < arr.getSize(); i++) {
        if (arr.get(i) > sum) {
            count++;
            indices.push_back(i);
        }
    }

    cout << "Task 4: ���������� ��������� > ����� (" << sum << "): " << count << endl;
    if (count > 0) {
        cout << "������ (�� 0): ";
        for (size_t j = 0; j < indices.size(); j++) {
            cout << indices[j];
            if (j < indices.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }

    delete[] data; // ������� ������.
}

// ������� 5.

void task5(const string& filename) {
    int n = 0;
    int* data = nullptr;
    if (!readFile(filename, n, data)) {
        return;
    }

    Array arr(n);
    arr.fillFrom(data);

    if (n < 5) {
        cout << "Task 5: ������ ������� ���������!" << endl;
        delete[] data;
        return;
    }

    int maxSum = INT_MIN;
    int startIndex = 0;
    for (int i = 0; i <= n - 5; i++) {
        int curSum = arr.get(i) + arr.get(i + 1) + arr.get(i + 2) + arr.get(i + 3) + arr.get(i + 4);
        if (curSum > maxSum) {
            maxSum = curSum;
            startIndex = i;
        }
    }

    cout << "Task 5: ������������ ����� 5 ��������: " << maxSum << endl;
    cout << "��������: ";
    for (int j = startIndex; j < startIndex + 5; j++) {
        cout << arr.get(j);
        if (j < startIndex + 4) {
            cout << ", ";
        }
    }
    cout << endl;

    delete[] data;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc < 2) {
        cout << "������: ������� ����!" << endl;
        return 1;
    }
    string filename = argv[1];

    task4(filename);
    task5(filename);

    return 0;
}