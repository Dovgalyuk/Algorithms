#ifndef ALGORITHMS_TASK_H
#define ALGORITHMS_TASK_H

#include <fstream>
#include "vector.h"

enum State {
    PATH = -2,
    EMPTY = -1,
    VISITED = 1,
};

int reader(Vector* vec, std::ifstream& file);
bool find_path(Vector* vec, int rows);
void writer(Vector* vec, int rows, std::ofstream& output);

#endif
