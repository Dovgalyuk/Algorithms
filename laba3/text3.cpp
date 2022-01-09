#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include "queue.h"

const int main_peak = 0; // исходная вершина отсчета

int main() {
    std::ifstream is("../../laba3/input.txt");
    std::ofstream os("../../laba3/output.txt");
    if (is.is_open() && os.is_open()) {
        int count;
        is >> count; // читает кол-во вершин
        int matrix[count][count];
        int num;
        for (int i = 0; i < count; ++i) {
            for (int j = 0; j < count; ++j) {
                is >> num; // запись
                matrix[i][j] = num;
            }
        } // создали матрицу
        auto* queue = new Queue<int>;
        queue->insert(main_peak);
        bool was[count]; // чтобы не посчитать 1 вершмну 2жды
        for (int i = 0; i < count; ++i) { // инициализируем массив
            was[i] = false;
        }
        int lengths[count];
        int length = 1;
        for (int i = 0; i < count; ++i) { // инициализируем массив очень большими путями
            lengths[i] = INT_MAX;
        }
        lengths[main_peak] = 0; // размеры путей
        while (!queue->empty()) {
            int id = queue->get(); // взять первый элемент
            length = lengths[id] + 1; // путь до вершины пред + 1 до всех соседей  от main_peak
            queue->remove(); // удал вершину которую взяли id
            if (was[id]) {
                continue;
            }
            was[id] = true;
            for (int i = 0; i < count; ++i) { // есть ли соединение вершины i  с id
                if (matrix[id][i] && !was[i]) {
                    if (lengths[i] > length) { // если прошл найд разм больше, то прист min
                        lengths[i] = length;
                    }
                    queue->insert(i); // добавить в очередь на проверку
                }
            }
        }
        for (int i = 0; i < count; ++i) {
            os << lengths[i] << std::endl;
        }
        os.flush();
        os.close();
    } else {
        std::cout << "error";
    }
    return 0;
}