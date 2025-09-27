#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include "array.h"

using namespace std;

Array* array_create_and_read(ifstream& input)
{
    int n;
    if (!(input >> n) || n <= 0) {
        return nullptr;
    }

    Array* arr = array_create(n);
    for (int i = 0; i < n; i++)
    {
        int x;
        if (!(input >> x)) {
            array_delete(arr);
            return nullptr;
        }
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array* arr)
{
    int n = array_size(arr);
    if (n == 0) return;

    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += array_get(arr, i);

    double average = sum / n;

    cout << "Elements less than average (" << fixed << setprecision(2) << average << "):";

    bool found = false;
    for (int i = 0; i < n; i++) {
        int element = array_get(arr, i);
        if (element < average) {
            cout << " " << element;
            found = true;
        }
    }

    if (!found)
        cout << " none";
    cout << endl;
}

void task2(Array* arr)
{
    int n = array_size(arr);
    if (n == 0) return;

    map<int, int> frequency;
    for (int i = 0; i < n; i++) {
        frequency[array_get(arr, i)]++;
    }

    int max_count = 0;
    int most_frequent = array_get(arr, 0);

    for (const auto& pair : frequency) {
        if (pair.second > max_count) {
            max_count = pair.second;
            most_frequent = pair.first;
        }
    }

    cout << "Most frequent element: " << most_frequent << " (occurs " << max_count << " times)" << endl;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Cannot open file: " << argv[1] << endl;
        return 1;
    }

    Array* arr = nullptr;
    arr = array_create_and_read(input);
    if (!arr) {
        cerr << "Error reading first array" << endl;
        input.close();
        return 1;
    }
    task1(arr);
    array_delete(arr);

    arr = array_create_and_read(input);
    if (!arr) {
        cerr << "Error reading second array" << endl;
        input.close();
        return 1;
    }
    task2(arr);
    array_delete(arr);

    input.close();
    return 0;
}