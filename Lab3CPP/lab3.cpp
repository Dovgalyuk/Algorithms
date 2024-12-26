#include <iostream>
#include <fstream>
#include <vector>
#include "queue.h"

using namespace std;

vector<int> lab_3(const string& file_path, int a, int b) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Error opening file: " << file_path << endl;
        return {};
    }

    Queue *queue1 = queue_create();
    Queue *queue2 = queue_create();
    Queue *queue3 = queue_create();

    int num;
    while (file >> num) {
        if (num < a) {
            queue_insert(queue1, num);
        } else if (num <= b) {
            queue_insert(queue2, num);
        } else {
            queue_insert(queue3, num);
        }
    }

    file.close();

    vector<int> sorted_arr;
    while (!queue_empty(queue1)) {
        sorted_arr.push_back(queue_get(queue1));
        queue_remove(queue1);
    }
    while (!queue_empty(queue2)) {
        sorted_arr.push_back(queue_get(queue2));
        queue_remove(queue2);
    }
    while (!queue_empty(queue3)) {
        sorted_arr.push_back(queue_get(queue3));
        queue_remove(queue3);
    }

    queue_delete(queue1);
    queue_delete(queue2);
    queue_delete(queue3);
    return sorted_arr;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    int a, b;
    if (!(file >> a >> b)) {
        std::cout << "Error reading a and b from file\n";
        file.close();
        return 1;
    }

    std::vector<int> ans_arr(9);
    for (int i = 0; i < 9; i++) {
        if (!(file >> ans_arr[i])) {
            std::cout << "Error reading answer array from file\n";
            file.close();
            return 1;
        }
    }

    file.close();
    string filePath = argv[1];
    vector<int> sorted_arr = lab_3(filePath, a, b);

    if (sorted_arr.size() != 9)
    {
        std::cout << "Error, not 9 elements in sorted array" << endl;
        return 1;
    }

    bool is_solve = true;
    for (size_t i = 0; i < sorted_arr.size(); i++) {
        if (sorted_arr[i] != ans_arr[i]) {
            is_solve = false;
            break;
        }
    }
    if (!is_solve) {
        std::cout << "Invalid lab_3 test1 execution\n";
        return 1;
    }

    return 0;
}
