#include <iostream>
#include <fstream>
#include <iomanip>
#include "array.h"

using namespace std;

Array *array_create_and_read(ifstream &input);

void task2(const Array *arr, ostream &out)
{
    size_t n = array_size(arr);
    if (n < 5)
    {
        out << 0 << endl;
        return;
    }

    int sum = 0;
    for (size_t i = 0; i < 5; i++)
        sum += array_get(arr, i);

    int MAX = sum;

    for (size_t i = 5; i < n; i++)
    {
        sum += array_get(arr, i) - array_get(arr, i - 5);
        MAX = max(sum, MAX);
    }

    out << MAX << endl;
}
int main(int argc, char **argv) {

    if (argc < 3) {
        cerr << "Oshibka: Nedostatochno argumentov!" << endl;
        return 1;
    }

    string in_path = argv[1];
    string out_path = argv[2];


    ifstream input(in_path);
    if (!input.is_open()) {
        cerr << "Fayl dlya chteniya ne otkrylsya: " << in_path << endl;
        return 1;
    }


    ofstream file_output(out_path);
    if (!file_output.is_open()) {
        cerr << "Fayl dlya zapisi ne otkrylsya: " << out_path << endl;
        return 1;
    }


    Array *arr = array_create_and_read(input);
    if (arr != nullptr) {
        task2(arr, file_output);
        array_delete(arr);
    }

    input.close();
    file_output.close();
}

Array *array_create_and_read(ifstream &input)
{
    int n = 0;
    input >> n;

    Array *arr = array_create((size_t)n);

    for (int i = 0; i < n; ++i)
    {
        int x = 0;
        input >> x;
        array_set(arr, i, x);
    }

    return arr;
}