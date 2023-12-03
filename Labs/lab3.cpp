#include <iostream>
#include "queue.h"
#include <vector>
#include <fstream>
#include <sstream>

const size_t NUM_BITS = 2;

using namespace std;

void radixSort(vector<size_t>& numbers) {
    vector<Queue*> queues(1 << NUM_BITS);

    for (size_t bit = 0; bit < sizeof(size_t) * 8; bit += NUM_BITS) {
        for (size_t number : numbers) {
            size_t bitValue = (number >> bit) & ((1 << NUM_BITS) - 1);
            queue_insert(queues[bitValue], number);
        }

        numbers.clear();
        for (size_t i = 0; i < queues.size(); i++) {
            while (!queue_empty(queues[i])) {
                numbers.push_back(queue_get(queue[i]));
                queue_remove(queue[i]);
            }
        }
    }
}

int main() {
    ifstream inputFile("inputl3.txt");
    string line;
    vector<size_t> numbers;

    if (inputFile.is_open()) {
        getline(inputFile, line);
        istringstream iss(line);
        int num;
        while (iss >> num) {
            numbers.push_back(num);
        }
        inputFile.close();
    }
    else {
        cout << "File error" << endl;
        return 1;
    }

    radixSort(numbers);

    for (int number : numbers) {
        cout << number << " ";
    }
    cout << endl;

    return 0;
}
