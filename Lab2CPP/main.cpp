#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "stack.h"
#include "array.h"

using namespace std;

typedef vector<Data> VectorData;

void merge_range(VectorData& arr, int start, int mid, int end, VectorData& temp) {
    int i = start, j = mid, k = start;
    while (i < mid && j < end) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }
    while (i < mid) temp[k++] = arr[i++];
    while (j < end) temp[k++] = arr[j++];

    for (int idx = start; idx < end; ++idx) {
        arr[idx] = temp[idx];
    }
}

VectorData read_numbers_from_file(const string& filename) {
    VectorData numbers;
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

string vector_to_string(const VectorData& vec) {
    if (vec.empty()) return "";
    ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i > 0) oss << " ";
        oss << vec[i];
    }
    return oss.str();
}

VectorData merge_sort_iterative(VectorData arr) {
    if (arr.size() <= 1) return arr;

    struct Task {
        int start;
        int end;
        bool do_merge;
    };

    int n = arr.size();
    VectorData temp(n);

    vector<Task> storage;
    Stack* stack = stack_create();
    storage.push_back({ 0, n, false });
    stack_push(stack, static_cast<Data>(storage.size() - 1));
    while (!stack_empty(stack)) {
        int idx = stack_get(stack);
        stack_pop(stack);
        Task t = storage[idx];
        if (t.end - t.start <= 1) continue;
        if (t.do_merge) {
            merge_range(arr, t.start, (t.start + t.end) / 2, t.end, temp);
        }
        else {
            int mid = t.start + (t.end - t.start) / 2;
            storage.push_back({ t.start, t.end, true });
            stack_push(stack, static_cast<Data>(storage.size() - 1));
            storage.push_back({ mid, t.end, false });
            storage.push_back({ t.start, mid, false });
            stack_push(stack, static_cast<Data>(storage.size() - 2));
            stack_push(stack, static_cast<Data>(storage.size() - 1));
        }
    }

    stack_delete(stack);
    return arr;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Using " << argv[0] << endl;
        return 1;
    }
    string filename = argv[1];
    VectorData numbers = read_numbers_from_file(filename);
    if (numbers.empty()) {
        cout << endl;
        return 0;
    }
    VectorData sorted = merge_sort_iterative(numbers);
    cout << vector_to_string(sorted) << endl;

    return 0;
}