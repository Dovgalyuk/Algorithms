#include<iostream>
#include<fstream>
#include <vector>
#include <sstream>
#include "queue.h"

const size_t NUM_BITS = 2;

using namespace std;

vector<size_t> ReadNumFromFile(string filename);
void radixSort(vector<size_t>& numbers);
void printQueue(vector<size_t>& numbers);

int main()
{
    string filepath = "C:\\Users\\veniamin\\Documents\\GitHub\\Algorithms\\Lab3CPP\\input.txt";
    vector<size_t> numbers = ReadNumFromFile(filepath);

    radixSort(numbers);
    printQueue(numbers);

    int n;
    cin >> n;
    return 0;



}

vector<size_t> ReadNumFromFile(string filepath) {
    ifstream inputFile(filepath);
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
        return numbers;
    } else {
        cout << "File dont open"<<endl;
        int n;
        cin >> n;
        exit(1);
    }

}

void radixSort(vector<size_t>& numbers) {
    vector<Queue*> queues(1<<NUM_BITS);
    for (size_t i = 0; i != (1 << NUM_BITS); i++) {
        queues[i] = queue_create();
    }

    for (size_t bit = 0; bit < sizeof(size_t) * 8; bit += NUM_BITS) {
        for (size_t number : numbers) {
            size_t bitValue = (number >> bit) & ((1 << NUM_BITS) - 1);
            queue_insert(queues[bitValue], (Data)number);
        }

        numbers.clear();
        for (size_t i = 0; i < queues.size(); i++) {
            while (!queue_empty(queues[i])) {
                numbers.push_back(queue_get(queues[i]));
                queue_remove(queues[i]);
            }
        }
    }
    for (size_t i = 0; i != (1 << NUM_BITS); i++) {
        queue_delete(queues[i]);
    }
}

void printQueue(vector<size_t>& numbers){
    for (size_t number : numbers) {
        cout << number << " ";
    }
    cout << endl;
}