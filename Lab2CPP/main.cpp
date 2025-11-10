#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "stack.h"
#include "array.h"

using namespace std;

Array* merge_arrays(const Array* left, const Array* right) {
    size_t len_left = array_size(left);
    size_t len_right = array_size(right);
    size_t total_len = len_left + len_right;
    Array* merged = array_create(total_len);
    size_t i = 0, j = 0, k = 0;
    while (i < len_left && j < len_right) {
        Data l_val = array_get(left, i);
        Data r_val = array_get(right, j);
        if (l_val <= r_val) {
            array_set(merged, k++, l_val);
            i++;
        }
        else {
            array_set(merged, k++, r_val);
            j++;
        }
    }
    while (i < len_left) {
        array_set(merged, k++, array_get(left, i++));
    }
    while (j < len_right) {
        array_set(merged, k++, array_get(right, j++));
    }
    return merged;
}

vector<Data> read_numbers_from_file(const string& filename) {
    vector<Data> numbers;
    ifstream file(filename);
    if (!file.is_open()) {
        return numbers;
    }

    string line;
    getline(file, line);
    istringstream iss(line);
    Data num;
    while (iss >> num) {
        numbers.push_back(num);
    }

    return numbers;
}

string vector_to_string(const vector<Data>& vec) {
    if (vec.empty()) return "";
    ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i > 0) oss << " ";
        oss << vec[i];
    }
    return oss.str();
}

vector<Data> merge_sort_iterative(vector<Data> arr) {
    if (arr.size() <= 1) return arr;
    Stack* stack = stack_create();
    vector<Array*> storage;
    for (Data x : arr) {
        Array* single = array_create(1);
        array_set(single, 0, x);
        storage.push_back(single);
        stack_push(stack, static_cast<Data>(storage.size() - 1));
    }

    while (!stack_empty(stack)) {
        Data idx_right = stack_get(stack);
        stack_pop(stack);
        if (stack_empty(stack)) {
            Array* result = storage[idx_right];
            arr.clear();
            for (size_t i = 0; i < array_size(result); ++i) {
                arr.push_back(array_get(result, i));
            }
            array_delete(result);
            storage[idx_right] = nullptr;
            break;
        }

        Data idx_left = stack_get(stack);
        stack_pop(stack);

        Array* left = storage[idx_left];
        Array* right = storage[idx_right];
        storage[idx_left] = nullptr;
        storage[idx_right] = nullptr;

        Array* merged = merge_arrays(left, right);
        storage.push_back(merged);
        stack_push(stack, static_cast<Data>(storage.size() - 1));

        array_delete(left);
        array_delete(right);
    }

    stack_delete(stack);
    for (Array* a : storage) {
        if (a != nullptr) {
            array_delete(a);
        }
    }

    return arr;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Использование: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    string filename = argv[1];
    vector<Data> numbers = read_numbers_from_file(filename);
    if (numbers.empty()) {
        cout << endl;
        return 0;
    }
    vector<Data> sorted = merge_sort_iterative(numbers);
    cout << vector_to_string(sorted) << endl;

    return 0;
}