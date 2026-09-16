#include "array.h"
#include <fstream>
#include <iostream>

using namespace std;

void free_int(Data d) {
    delete static_cast<int*>(d);
}

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        cerr << "Задание 2: <input_file> [output_file]\n";
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
        cerr << "Ошибка открытия\n";
        return 1;
    }

    size_t n;
    if (!(input >> n) || n == 0) {
        return 0;
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

    size_t repeat = 1;
    for (size_t i = 1; i < array_size(nums); ++i) {
        int curr = *static_cast<int*>(array_get(nums, i));
        int prev = *static_cast<int*>(array_get(nums, i - 1));

        if (curr == prev) {
            ++repeat;
        } else {
            *output << prev << ' ' << repeat << '\n';
            repeat = 1;
        }
    }

    int last = *static_cast<int*>(array_get(nums, array_size(nums) - 1));
    *output << last << ' ' << repeat << "\n\n";

    array_delete(nums);
    return 0;
}
