#ifndef ALGORITHMS_TASK_H
#define ALGORITHMS_TASK_H

enum State {
    PATH = -2,
    EMPTY = -1,
    VISITED = 1,
};

int reader(Vector* vec, std::ifstream& file);
bool find_path(Vector* vec, int rows);


#endif
