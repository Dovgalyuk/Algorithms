#include <iostream>
#include <fstream>
#include <climits>
#include "array.h"

using namespace std;

Array* array_create_and_read_from_file(ifstream &input);
int quest_one(const Array* arr);
int quest_two(const Array* arr);
bool test_quest_one(int a);
bool test_quest_two(int a);

int main(int argc, char **argv)
{
    ifstream input;
    input.open(argv[1]);
    if (!input.is_open()) {
        cerr << "Error opening file!" << endl;
        return EXIT_FAILURE;
    }
    Array *arr = array_create_and_read_from_file(input);
    cout << "Quest one: " <<quest_one(arr) << endl;
    if(!(test_quest_one(quest_one(arr)))) return 1;
    cout << "Quest two: " <<quest_two(arr) << endl;
    if(!(test_quest_two(quest_two(arr)))) return 1;
    array_delete(arr);
    input.close();
    return 0;
}

Array* array_create_and_read_from_file(ifstream &input) {
    size_t size;
    input >> size;
    Array* arr = array_create(size);
    for (size_t i = 0; i < size; i++) {
        int a;
        input >> a;
        array_set(arr, i, a);
    }
    return arr;
}

int quest_one(const Array* arr) {
    int count = 0;
    size_t i = 0;
    while (i < array_size(arr)) {
        int num = array_get(arr, i);
        int j = 2;
        while (j <= 9) {
            if (num % j == 0) {
                count++;
                j = 10;
            } else {
                j++;
            }
        }
        i++;
    }
    return count;
}

int quest_two(const Array* arr) {
    size_t size = array_size(arr);
    if(size < 5) {
        cout << "Error array >5 elem" << endl;
        return 0;
    }
    int max_sum = INT_MIN;
    int sum = 0;
    for (size_t i = 0; i < 5; i++) {
        sum += array_get(arr, i);
    }
    max_sum = sum;
    for (size_t i = 5; i < size; i++) {
        sum += array_get(arr, i) - array_get(arr, i-5);
        if(sum > max_sum) {
            max_sum = sum;
        }
    }
    return max_sum;
}

bool test_quest_one(int a) {
    if(a != 9) {
        cout << "Test one NOT completed" << endl;
        return false;
    }
    cout << "Test one completed" << endl;
    return true;
}

bool test_quest_two(int a) {
    if(a != 40) {
        cout << "Test two NOT completed" << endl;
        return false;
    }
    cout << "Test two completed" << endl;
    return true;
}
