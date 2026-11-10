#include <fstream>
#include "vector.h"
#include "task.h"

int main() {
    Vector* vec = vector_create();
    int rows = 0;
    std::ifstream input("input.txt");
    if (input.is_open()) {
         rows = reader(vec, input);
    }

    bool havePath = find_path(vec, rows);
    if (havePath) {
        std::ofstream output("output.txt");
        if (output.is_open()) {
            writer(vec, rows, output);
        }
    }

    vector_delete(vec);

    return 0;
}