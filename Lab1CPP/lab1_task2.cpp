#include <iostream>
#include <fstream>
#include <iomanip>
#include "array.h"

using namespace std;

Array *array_create_and_read(ifstream &input);

void task2(const Array *arr, ostream &out)
{
    size_t n = array_size(arr);
    int MAX = 0, b = 0;

    for (size_t i = 0; i + 4 < n; i++)
    {
        b = array_get(arr, i) + array_get(arr, i + 1) + array_get(arr, i + 2)
            + array_get(arr, i + 3) + array_get(arr, i + 4);
        MAX = max(b, MAX);
    }

    out << MAX << endl;
    out << "MaxSum: sum=" << MAX << endl;
}

int main(int argc, char **argv) {
    string in_path = (argc >= 2) ? argv[1] : "test_1";
    string out_path = (argc >= 3) ? argv[2] : "result_2";

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
        task2(arr, out);
        array_delete(arr);
    }

    input.close();
    return 0;
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