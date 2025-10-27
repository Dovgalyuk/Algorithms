#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <memory>
#include "array.h"

using namespace std;

unique_ptr<Array> array_create_and_read(ifstream& input)
{
    int n;
    input >> n;
    /* Create array */
    auto arr = make_unique <Array>(n);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        input >> x;
        arr->set(i, x);
    }
    return arr;
}

void task1(Array* arr)
{
    int rainy_days = 0;
    int total_precipitation = 0;

    for (size_t i = 0; i < arr->size(); ++i) {
        int precipitation = arr->get(i);
        if (precipitation > 0) {
            rainy_days++;
            total_precipitation += precipitation;
        }
    }

    if (rainy_days > 0) {
        double average = static_cast<double>(total_precipitation) / rainy_days;
        cout << "Average precipitation on rainy days: " << average << endl;
    }
    else {
        cout << "No rainy days" << endl;
    }
}

void task2(Array *arr)
{
    map<int, int> frequency;
    for (size_t i = 0; i < arr->size(); ++i) {
        frequency[arr->get(i)]++;
    }

    vector<int> result;
    for (const auto& pair : frequency) {
        if (pair.second == 2) {
            result.push_back(pair.first);
        }
    }

    cout << "Elements that appear exactly twice: ";
    if (result.empty()) {
        cout << "none";
    }
    else {
        for (size_t i = 0; i < result.size(); ++i) {
            cout << result[i];
            if (i < result.size() - 1) {
                cout << " ";
            }
        }
    }
    cout << endl;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Cannot open file: " << argv[1] << endl;
        return 1;
    }

    auto arr = array_create_and_read(input);
    cout << "Task1 - Precipitation analysis:" << endl;
    task1(arr.get());
    
    /* Create another array here */
    arr = array_create_and_read(input);
    cout << "Task2 - Elements appearing exactly twice:" << endl;
    task2(arr.get());
    
    input.close();
    return 0;
}
