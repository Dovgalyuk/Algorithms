#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include "queue.h"

const int main_peak = 0;

int main() {
    std::ifstream is("../../laba3/input.txt");
    std::ofstream os("../../laba3/output.txt");
    if (is.is_open() && os.is_open()) {
        int count;
        is >> count;
        int matrix[count][count];
        int num;
        for (int i = 0; i < count; ++i) {
            for (int j = 0; j < count; ++j) {
                is >> num;
                matrix[i][j] = num;
            }
        }
        auto* queue = new Queue<int>;
        queue->insert(main_peak);
        bool was[count];
        for (int i = 0; i < count; ++i) {
            was[i] = false;
        }
        int lengths[count];
        int length = 1;
        for (int i = 0; i < count; ++i) {
            lengths[i] = INT_MAX;
        }
        lengths[main_peak] = 0;
        while (!queue->empty()) {
            int id = queue->get();
            length = lengths[id] + 1;
            queue->remove();
            if (was[id]) {
                continue;
            }
            was[id] = true;
            for (int i = 0; i < count; ++i) {
                if (matrix[id][i] && !was[i]) {
                    if (lengths[i] > length) {
                        lengths[i] = length;
                    }
                    queue->insert(i);
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