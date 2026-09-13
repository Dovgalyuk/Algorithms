#include "general.h"

void task2(Array *arr) { // Task 2: Print elements that are not divisible by any other element in the array
    size_t size = array_size(arr);
    bool first = true;

    for (size_t i = 0; i < size; i++) {
        int value = array_get(arr, i);
        bool flag = false;
        for (size_t j = 0; j < size; j++) {
            if (i == j) continue; // Skip the same index

            int del = array_get(arr, j);
            if (del == 0) continue; // Avoid division by zero

            if (value % del == 0) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            if (!first) cout << " ";
            cout << value;
            first = false;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    Array *arr = read_file_and_create_array(input);
    if (arr == nullptr) {
        cerr << "Error reading array from file." << endl;
        return 1;
    }

    task2(arr);

    array_delete(arr);
    input.close();

    return 0;
}