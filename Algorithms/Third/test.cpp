#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"

const int main_peak = 0;

int main() {
    std::ifstream is("../../../Algorithms/Third/input.txt");
    std::ofstream os("../../../Algorithms/Third/output.txt");
    if (is.is_open() && os.is_open()) {
        int count;
        is >> count;
        int matrix[count][count];
        int num;
        int id;
        for (int i = 0; i < count; ++i) {
            for (int j = 0; j < count; ++j) {
                is >> num;
                matrix[i][j] = num;
            }
        }
        auto* queue = new Queue<int>;
        queue->insert(main_peak);
        bool was[count];
        was[main_peak] = true;
        int length = 0;
        os << length++ << std::endl;
        while (!queue->empty()) {
            id = queue->get();
            queue->remove();
            for (int i = 0; i < count; ++i) {
                if (matrix[id][i] && !was[i]) {
                    os << length << std::endl;
                    was[i] = true;
                    queue->insert(i);
                }
            }
            length++;
        }
        os.flush();
        os.close();
    } else {
        std::cout << "error";
    }
    return 0;
}