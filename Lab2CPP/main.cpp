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

void push_task(Stack* stack, int start, int end, bool do_merge) {
    stack_push(stack, static_cast<Data>(start));
    stack_push(stack, static_cast<Data>(end));
    stack_push(stack, static_cast<Data>(do_merge ? 1 : 0));
}

bool pop_task(Stack* stack, int& start, int& end, bool& do_merge) {
    if (stack_empty(stack)) {
        return false;
    }

    int merge_val = static_cast<int>(stack_get(stack));
    stack_pop(stack);
    do_merge = (merge_val != 0);
    end = static_cast<int>(stack_get(stack));
    stack_pop(stack);
    start = static_cast<int>(stack_get(stack));
    stack_pop(stack);

    return true;
}

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
    int n = arr.size();
    VectorData temp(n);
    Stack* stack = stack_create();
    push_task(stack, 0, n, false);
    while (!stack_empty(stack)) {
        int start, end;
        bool do_merge;
        if (!pop_task(stack, start, end, do_merge)) continue;
        if (end - start <= 1) continue;
        if (do_merge) {
            merge_range(arr, start, (start + end) / 2, end, temp);
        }
        else {
            int mid = start + (end - start) / 2;
            push_task(stack, start, end, true);
            push_task(stack, mid, end, false);
            push_task(stack, start, mid, false);
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