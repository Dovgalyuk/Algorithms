#include "apfel.h"

bool run_task2(Array* arr, ofstream& output) {
    size_t size = array_size(arr);

    Array* result_mask = array_create(size);

    for (size_t i = 0; i < size; i++) {
        int current = array_get(arr, i);
        bool is_indivisible = true;

        if (current == 0) {
            is_indivisible = false;
        }
        else {
            for (size_t j = 0; j < size; j++) {
                if (i == j) continue;

                int other = array_get(arr, j);
                if (other != 0 && current % other == 0) {
                    is_indivisible = false;
                    break;
                }
            }
        }

        array_set(result_mask, i, is_indivisible ? 1 : 0);
    }

    bool first = true;
    for (size_t i = 0; i < size; i++) {
        if (array_get(result_mask, i) == 1) {
            if (!first) {
                cout << " ";
                output << " ";
            }
            cout << array_get(arr, i);
            output << array_get(arr, i);
            first = false;
        }
    }
    cout << endl;
    output << endl;

    array_delete(result_mask);
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
        output.open("output_task2.txt");
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

    bool success = run_task2(arr, output);

    array_delete(arr);
    input.close();
    output.close();

    return success ? 0 : 1;
}