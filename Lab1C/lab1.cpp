#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
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
    size_t n = array_size(arr);
    if (n == 0) {
        cout << "Task1: array is empty" << endl;
        return;
    }

    double sum = 0;
    for (size_t i = 0; i < n; i++)
        sum += array_get(arr, i);

    double average = sum / n;

    int closest = array_get(arr, 0);
    double min_diff = fabs(closest - average);

    for (size_t i = 1; i < n; i++) {
        int element = array_get(arr, i);
        double diff = fabs((double)element - average);
        if (diff < min_diff) {
            min_diff = diff;
            closest = element;
        }
    }

    cout << "Task1: element closest to average (" << fixed << setprecision(2) << average << ") is " << closest << endl;
}

void task2(Array* arr, ifstream& input)
{
    size_t n = array_size(arr);
    if (n == 0) {
        cout << "Task2: array is empty" << endl;
        return;
    }

    int direction, steps;
    if (!(input >> direction >> steps)) {
        cout << "Error reading direction and steps" << endl;
        return;
    }

    size_t step_count = static_cast<size_t>(steps);
    if (step_count > n) step_count = n;
    if (steps < 0) step_count = 0;

    if (direction == 0) {
        for (size_t i = 0; i + step_count < n; i++) {
            array_set(arr, i, array_get(arr, i + step_count));
        }

        for (size_t i = n - step_count; i < n; i++) {
            array_set(arr, i, 0);
        }
    }
    else {
<<<<<<< HEAD

=======
       
>>>>>>> 1bfc6b8b4b18bf3bcbae8f6a4e143ec7da3dacea
        for (size_t i = n - 1; i >= step_count; i--) {
            array_set(arr, i, array_get(arr, i - step_count));
        }

        for (size_t i = 0; i < step_count; i++) {
            array_set(arr, i, 0);
        }
    }

    cout << "Task2: shifted array = ";
    for (size_t i = 0; i < n; i++)
        cout << array_get(arr, i) << " ";
    cout << endl;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input;
    input.open(argv[1]);
    if (!input.is_open()) {
        cerr << "Cannot open file: " << argv[1] << endl;
        return 1;
    }

    Array* arr = array_create_and_read(input);
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
    task2(arr, input);
    array_delete(arr);

    input.close();
    return 0;
}