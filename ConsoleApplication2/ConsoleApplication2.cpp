#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Array {
    int* data;
    int size;
};
bool Palindrome(int n) {
    if (n < 0) return false;
    if (n < 10) return true;
    int original = n;
    int reversed = 0;
    while (n > 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    return original == reversed;
}
void fillPalindromes(Array& arr) {
    int count = 0;
    int num = 0;
    while (count < arr.size) {
        if (Palindrome(num)) {
            arr.data[count] = num;
            count++;
        }
        num++;
    }
}
void printArray(const Array& arr) {
    for (int i = 0; i < arr.size; i++) {
        cout << arr.data[i] << " ";
    }
    cout << endl;
}
int SizeFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return -1;
    }
    int size;
    file >> size;
    if (size <= 0) {
        cerr << "Неверный размер массива: " << size << endl;
        return -1;
    }
    return size;
}
void ArrayFromFile(const string& filename, Array& arr) {
    ifstream file(filename);
    int size;
    file >> size;
    for (int i = 0; i < size; i++) {
        file >> arr.data[i];
    }
}
int findMin(const Array& arr) {
    vector<int> evenNumbers;
    for (int i = 0; i < arr.size; i++) {
        if (arr.data[i] % 2 == 0) {
            evenNumbers.push_back(arr.data[i]);
        }
    }
    if (evenNumbers.size() < 2) {
        return -1;
    }
    sort(evenNumbers.begin(), evenNumbers.end());
    int minDiff = INT_MAX;
    for (int i = 1; i < evenNumbers.size(); i++) {
        if (evenNumbers[i] != evenNumbers[i - 1]) {
            int diff = evenNumbers[i] - evenNumbers[i - 1];
            if (diff < minDiff) {
                minDiff = diff;
            }
        }
    }

    return minDiff;
}
int main() {
    setlocale(LC_ALL, "ru");

    int size1 = SizeFile("input1.txt");
    if (size1 <= 0) return 1;
    int size2 = SizeFile("input2.txt");
    if (size2 <= 0) return 1;
    // палиндромы
    Array arr1;
    arr1.size = size1;
    arr1.data = new int[size1];
    fillPalindromes(arr1);
    cout << "Массив палиндромов: ";
    printArray(arr1);
    delete[] arr1.data;
    // разность
    Array arr2;
    arr2.size = size2;
    arr2.data = new int[size2];
    ArrayFromFile("input2.txt", arr2);
    int result = findMin(arr2);
    cout << "Минимальная разность четных элементов: " << result << endl;
    delete[] arr2.data;

}
