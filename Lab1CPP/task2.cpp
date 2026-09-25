#include "common.h"

bool task2(Array *arr, ifstream &input, ofstream &output) {
    int direction, steps;

    if (!(input >> direction >> steps)) {
        print_error("Ошибка: не удалось прочитать параметры сдвига", output);
        return false;
    }

    size_t size = array_size(arr);

    print_array(cout, arr);
    print_array(output, arr);

    Array* temp = array_create(size);

    if (direction == 0) {
        for (size_t i = 0; i < size; i++) {
            if ((int)i + steps < (int)size) {
                array_set(temp, i, array_get(arr, i + steps));
            } else {
                array_set(temp, i, 0);
            }
        }
    } else if (direction == 1) {
        for (size_t i = 0; i < size; i++) {
            if ((int)i - steps >= 0) {
                array_set(temp, i, array_get(arr, i - steps));
            } else {
                array_set(temp, i, 0);
            }
        }
    } else {
        print_error("Ошибка: неверное направление", output);
        array_delete(temp);
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        array_set(arr, i, array_get(temp, i));
    }

    array_delete(temp);

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
        output.open("output_task2.txt");
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

    if (!task2(arr, input, output)) {
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
