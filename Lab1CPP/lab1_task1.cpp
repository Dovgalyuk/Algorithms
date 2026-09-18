#include <iostream>
#include <fstream>
#include <iomanip>
#include "array.h"

using namespace std;

// Читает из файла количество элементов и заполняет ими массив
Array *array_create_and_read(ifstream &input);

struct Decades
{
    long long sum = 0;
    size_t cnt = 0;

    double average() const
    {
        return cnt == 0 ? 0.0 : static_cast<double>(sum) / static_cast<double>(cnt);
    }
};

void computeDecades(const Array *data, Decades decades[3])
{
    size_t n = array_size(data);
    if (n == 0)
        throw std::runtime_error("Massiv pust");

    size_t decadeSize = n / 3;
    if (decadeSize == 0)
        throw std::runtime_error("Slishkom malo elementov dlya deleniya na tri dekady");

    size_t start = 0;
    for (int i = 0; i < 3; i++)
    {
        size_t end = (i == 2) ? n : start + decadeSize;
        for (size_t j = start; j < end; j++)
        {
            decades[i].sum += array_get(data, j);
            decades[i].cnt++;
        }
        start = end;
    }
}


void task1(const Array *arr, ostream &out)
{
    Decades decades[3];
    computeDecades(arr, decades);

    out << fixed << setprecision(2)
        << decades[0].average() << " "
        << decades[1].average() << " "
        << decades[2].average() << "\n";
}

int main(int argc, char **argv)
{

    if (argc < 3) {
        cerr << "Oshibka: Nedostatochno argumentov!" << endl;
        cerr << "Ispolzovanie: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    string in_path = argv[1];
    string out_path = argv[2];


    ifstream input(in_path);
    if (!input.is_open()) {
        cerr << "Fayl dlya chteniya ne otkrylsya: " << in_path << endl;
        return 1;
    }

    ofstream file_output(out_path, ios::binary);
    if (!file_output.is_open()) {
        cerr << "Fayl dlya zapisi ne otkrylsya: " << out_path << endl;
        return 1;
    }

    Array *arr = array_create_and_read(input);
    if (arr != nullptr) {
        task1(arr, file_output);
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