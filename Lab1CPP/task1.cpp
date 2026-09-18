#include "apfel.h"

long long factorial(int n) {
    if (n < 0) return 0;
    long long res = 1;
    for (int i = 1; i <= n; ++i) {
        res *= i;
    }
    return res;
}

bool run_task1(Array* arr, ofstream& output) {
    size_t size = array_size(arr);

    for (size_t i = 0; i < size; i++) {
        int val = array_get(arr, i);
        if (val < 0) {
            print_error("Ошибка: в массиве присутствует отрицательное число для факториала", output);
            return false;
        }
        array_set(arr, i, (int)factorial(val));
    }

    print_array(cout, arr);
    print_array(output, arr);

    return true;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Использование: " << argv[0] << " <входной_файл> [выходной_файл]" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cout << "Ошибка открытия входного файла" << endl;
        return 1;
    }

    ofstream output;
    if (argc >= 3) {
        output.open(argv[2]);
    }
    else {
        output.open("output_task1.txt");
    }

    if (!output.is_open()) {
        cout << "Ошибка создания выходного файла" << endl;
        input.close();
        return 1;
    }

    Array* arr = array_create_and_read(input);
    if (arr == nullptr) {
        print_error("Ошибка: неверный размер массива или данные", output);
        input.close();
        output.close();
        return 1;
    }

    bool success = run_task1(arr, output);

    array_delete(arr);
    input.close();
    output.close();

    return success ? 0 : 1;
}