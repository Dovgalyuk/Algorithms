#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "stack.h"

using namespace std;

vector<Data> merge(const vector<Data>& left, const vector<Data>& right) {
    vector<Data> result;
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) result.push_back(left[i++]);
        else result.push_back(right[j++]);
    }
    while (i < left.size()) result.push_back(left[i++]);
    while (j < right.size()) result.push_back(right[j++]);
    return result;
}

vector<Data> read_numbers_from_file(const string& filename) {
    vector<Data> numbers;
    ifstream file(filename);
    if (!file.is_open()) return numbers;
    string line;
    getline(file, line);
    istringstream iss(line);
    Data num;
    while (iss >> num) numbers.push_back(num);
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
    vector<vector<Data>> storage;
    Stack* stack = stack_create();
    for (Data x : arr) {
        storage.push_back({ x });
        stack_push(stack, static_cast<Data>(storage.size() - 1));
    }

    while (!stack_empty(stack)) {
        Data idx_right = stack_get(stack);
        stack_pop(stack);

        if (stack_empty(stack)) {
            arr = storage[idx_right];
            break;
        }

        Data idx_left = stack_get(stack);
        stack_pop(stack);

        vector<Data> merged = merge(storage[idx_left], storage[idx_right]);
        storage.push_back(merged);
        stack_push(stack, static_cast<Data>(storage.size() - 1));
    }

    stack_delete(stack);
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