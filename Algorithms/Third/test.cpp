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
        int id = 0;
        while (is >> num) {
            matrix[id / count][id % count] = num;
            id++;
        }
        auto* queue = new Queue<int>;
        queue->insert(main_peak);
        std::string was = std::to_string(main_peak);
        int length = 0;
        os << length++ << std::endl;
        while (!queue->empty()) {
            id = queue->get();
            queue->remove();
            for (int i = 0; i < count; ++i) {
                if (matrix[id][i] && was.find(std::to_string(i)) == std::string::npos) {
                    os << length << std::endl;
                    was += std::to_string(i);
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