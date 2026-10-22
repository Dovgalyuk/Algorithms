#include "common.h"

bool task1(Array *arr, ifstream &input, ofstream &output) {
    int k1, k2;

    if (!(input >> k1 >> k2)) {
        print_error("Ошибка: не удалось прочитать индексы", output);
        return false;
    }

    size_t size = array_size(arr);

    if (k1 < 0 || k1 >= (int)size || k2 < 0 || k2 >= (int)size) {
        print_error("Ошибка: индексы k1/k2 выходят за пределы массива", output);
        return false;
    }

    print_array(cout, arr);
    print_array(output, arr);

    int elem_k1 = array_get(arr, k1);
    int elem_k2 = array_get(arr, k2);

    for (size_t i = 0; i < size; i++) {
        int current = array_get(arr, i);
        if (current > 0) {
            array_set(arr, i, current - elem_k1);
        } else {
            array_set(arr, i, current - elem_k2);
        }
    }

    print_array(cout, arr);
    print_array(output, arr);

    return true;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Использование: " << argv[0] << " <входной_файл> [выходной_файл]" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return 1;
    }

    ofstream output;
    if (argc >= 3) {
        output.open(argv[2]);
    } else {
        output.open("output_task1.txt");
    }

    if (!output.is_open()) {
        cout << "Ошибка создания выходного файла" << endl;
        input.close();
        return 1;
    }

    Array *arr = array_create_and_read(input);

    if (arr == nullptr) {
        cerr << "Ошибка: неверный размер массива" << endl;
        input.close();
        output.close();
        return 1;
    }

    if (!task1(arr, input, output)) {
        array_delete(arr);
        input.close();
        output.close();
        return 1;
    }

    array_delete(arr);

    input.close();
    output.close();
    return 0;
}
