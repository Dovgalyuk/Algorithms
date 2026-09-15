#include <iostream>
#include <fstream>
#include <iomanip>
#include "array.h"

using namespace std;

// Читает из файла количество элементов и заполняет ими массив
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

struct Decades
{
    long long sum = 0;
    size_t cnt = 0;

    double average() const // Считает среднее арифметическое
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

// Задание 1: передаем ostream (это может быть cout или ofstream)
void task1(const Array *arr, ostream &out)
{
    Decades decades[3];
    computeDecades(arr, decades);

    out << fixed << setprecision(2);
    for (int i = 0; i < 3; i++)
        out << "   " << i + 1 << " decada: " << decades[i].average() << endl;
    out << endl;

    out << "Decade: " << decades[0].average() << " "
        << decades[1].average() << " " << decades[2].average() << endl;
}

// Задание 2: передаем ostream
void task2(const Array *arr, ostream &out)
{
    size_t n = array_size(arr);
    int MAX = 0, b = 0;

    // Инициализируем MAX минимальным значением на случай отрицательных чисел
    if (n >= 5) {
        MAX = array_get(arr, 0) + array_get(arr, 1) + array_get(arr, 2) +
              array_get(arr, 3) + array_get(arr, 4);
    }

    for (size_t i = 0; i + 4 < n; i++)
    {
        b = array_get(arr, i) + array_get(arr, i + 1) + array_get(arr, i + 2)
            + array_get(arr, i + 3) + array_get(arr, i + 4);
        MAX = max(b, MAX);
    }

    out << MAX << endl;
    out << "MaxSum: sum=" << MAX << endl;
}
int main(int argc, char **argv)
{

    string in_path = (argc >= 2) ? argv[1] : "test_1";
    string out_path = (argc >= 3) ? argv[2] : "result";

    ifstream input(in_path);
    if (!input.is_open())
    {
        cout << "Fayl ne otkrylsya: " << in_path << "\n";
        return 1;
    }


    bool writing = false;
    if (argc >= 3)
    {
        writing = true;
    }
    else
    {

        string s;
        while (true)
        {
            cout << "Zapisat rezultat v fayl?(y/n): ";
            cin >> s;

            if (s == "y" || s == "yes" || s == "da") {
                writing = true;
                break;
            } else if (s == "n" || s == "net" || s == "no") {
                writing = false;
                break;
            } else {
                cout << "Nekorrektnyy vvod, poprobuyte eshche raz\n";
            }
        }
    }

    // bool writing;
    // string s;
    // while (true) {
    //     cout << "Zapisat rezultat v fayl?(y/n): ";
    //     cin >> s;
    //
    //     if (s == "y" || s == "yes" || s == "da") {
    //         writing = true;
    //         break;
    //     } else if (s == "n" || s == "net" || s == "no") {
    //         writing = false;
    //         break;
    //     } else {
    //         cout << "Nekorrektnyy vvod, poprobuyte eshche raz" << endl;
    //     }
    // }

    ofstream file_output;
    if (writing)
    {
        file_output.open(out_path);
        if (!file_output.is_open()) {
            cout << "Cannot open output file. Fallback to console.\n";
        } else {
            cout << "Resultaty budut zapisany v " << out_path << "\n\n";
        }
    }


    ostream &out = file_output.is_open() ? file_output : cout;

    Array *arr = array_create_and_read(input);
    if (arr != nullptr) {
        task1(arr, out);
        array_delete(arr);
    }


    arr = array_create_and_read(input);
    if (arr != nullptr) {
        task2(arr, out);
        array_delete(arr);
    }

    input.close();
    return 0;
}