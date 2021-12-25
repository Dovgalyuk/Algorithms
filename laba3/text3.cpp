#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
        auto* queue = new Queue<std::vector<int>>;
        queue->insert({main_peak});
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
            std::vector<int> peaks = queue->get();
            std::vector<int> next;
            queue->remove();
            for (const auto &id : peaks){
                if (was[id]) {
                    continue;
                }
                was[id] = true;
                for (int i = 0; i < count; ++i) {
                    if (matrix[id][i] && !was[i]) {
                        if (lengths[i] > length) {
                            lengths[i] = length;
                        }
                        next.push_back(i);
                    }
                }
            }
            if (!next.empty()) {
                queue->insert(next);
            }
            length++;
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