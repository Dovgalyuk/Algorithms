#include <iostream>
#include "queue.h"
#include <vector>
#include <fstream>
#include <sstream>

const int NUM_BITS = 2;

using namespace std;

void radixSort(vector<int>& numbers) {
    vector<Queue*> queues(1 << NUM_BITS);

    for (int bit = 0; bit < sizeof(int) * 8; bit += NUM_BITS) {
        for (int number : numbers) {
            int bitValue = (number >> bit) & ((1 << NUM_BITS) - 1);
            queue_insert(queues[bitValue], number);
        }

        numbers.clear();
        for (Queue& queue : queues) {
            while (!queue_empty(queue)) {
                numbers.push_back(queue_get(queue));
                queue_remove(queue);
            }
        }
    }
}

int main() {
    ifstream inputFile("inputl3.txt");
    string line;
    vector<int> numbers;

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
