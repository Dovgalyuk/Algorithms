#include "array.h"
#include <fstream>
#include <iostream>

using namespace std;

void free_int(Data d) {
    delete static_cast<int*>(d);
}

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        cerr << "Ошибка <input_file> [output_file]\n";
        return 1;
    }

    ifstream input(argv[1]);
    ofstream file_output;
    ostream* output = &cout;
    if (argc == 3) {
        file_output.open(argv[2]);
        output = &file_output;
    }

    if (!input.is_open() || !output->good()) {
        cerr << "Ошибка\n";
        return 1;
    }

    size_t n;
    if (!(input >> n)) {
        return 1;
    }

    Array* nums = array_create(n, free_int);
    for (size_t i = 0; i < n; ++i) {
        int val;
        if (!(input >> val)) {
            cerr << "Ошибка чтения\n";
            array_delete(nums);
            return 1;
        }
        array_set(nums, i, new int(val));
    }

    int two = 0, three = 0, four = 0, five = 0;
    for (size_t i = 0; i < array_size(nums); ++i) {
        int val = *static_cast<int*>(array_get(nums, i));
        if (val == 2) ++two;
        else if (val == 3) ++three;
        else if (val == 4) ++four;
        else if (val == 5) ++five;
    }

    *output << "5: " << five << '\n';
    *output << "4: " << four << '\n';
    *output << "3: " << three << '\n';
    *output << "2: " << two << "\n\n";
 
    array_delete(nums);
    return 0;
}
