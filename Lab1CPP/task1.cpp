#include "general.h"

void task1(Array *arr) { // Task 1: Print indices of elements less than the average of min and max
    size_t size = array_size(arr);
    int min_value = array_get(arr, 0);
    int max_value = array_get(arr, 0);

    for (size_t i = 1; i < size; i++) {
        int value = array_get(arr, i);

        if (value < min_value) {
            min_value = value;
        }

        if (value > max_value) {
            max_value = value;
        }
    }

    double average = static_cast<double>(min_value + max_value) / 2.0;

    bool first = true;
    for (size_t i = 0; i < size; i++) {
        int value = array_get(arr, i);
        if (value < average) {
            if (!first) cout << " ";
            cout << i;
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

    task1(arr);

    array_delete(arr);
    input.close();

    return 0;
}