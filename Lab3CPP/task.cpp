#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "queue.h"
#include "vector.h"
#include "task.h"

int reader(Vector* vec, std::ifstream& input) {
    std::string line;
    Vector* values = vector_create();

    int rows = 0;

    while (std::getline(input, line)) {
        std::istringstream stream(line);

        int value;
        bool isValue = false;

        while (stream >> value) {
            size_t index = vector_size(values);
            vector_set(values, index, value);

            isValue = true;
        }

        if (isValue) {
            rows++;
        }
    }

    int middle = rows/2;
    int index = 0;

    for (int i = 0; i < rows*rows; i++) {
        vector_set(vec, i, EMPTY);
    }

    for (int i = 0; i < rows; i++) {
        int distance = std::abs(middle - i);

        for (int j = distance; j < rows - distance; j++) {
            vector_set(vec, i*rows + j, vector_get(values, index));
            index++;
        }
    }

    vector_delete(values);

    return rows;
}

bool find_path(Vector* vec, int rows) {

    if (!vec || rows <= 0 || vector_size(vec) == 0) {
        return false;
    }

    Queue* queue = queue_create();
    Vector* visited = vector_create();
    Vector* parent = vector_create();

    int size = rows * rows;

    for (int i = 0; i < size; i++) {
        vector_set(visited, i, 0);
        vector_set(parent, i, -1);
    }

    int begin = (rows/2) * rows;
    int end = begin + rows - 1;

    int directions[4] = {-rows, rows, -1, 1};

    queue_insert(queue, begin);
    vector_set(visited, begin, VISITED);

    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove(queue);

        if (current == end) {
            break;
        }

        for (int i = 0; i < 4; i++) {
            int next = current + directions[i];

            if (next < 0 || next >= size) {
                continue;
            }

            if (i == 2 && current % rows == 0) {
                continue;
            }

            if (i == 3 && current % rows == rows - 1) {
                continue;
            }

            if (vector_get(visited, next) == VISITED) {
                continue;
            }

            if (vector_get(vec, next) == EMPTY) {
                continue;
            }

            int currentValue = vector_get(vec, current);
            int nextValue = vector_get(vec, next);

            if (std::abs(currentValue - nextValue) == 1) {
                vector_set(visited, next, VISITED);
                vector_set(parent, next, current);
                queue_insert(queue, next);
            }
        }
    }

    bool found = vector_get(visited, end) == VISITED;

    if (found) {
        int current = end;

        while (current != begin) {
            int prev = vector_get(parent, current);
            vector_set(vec, current, PATH);
            current = prev;
        }

        vector_set(vec, begin, PATH);
    }

    queue_delete(queue);
    vector_delete(visited);
    vector_delete(parent);

    return found;
}

void writer(Vector* vec, int rows, std::ofstream& output) {
    int middle = rows/2;

    for (int i = 0; i < rows; i++) {
        int distance = std::abs(middle - i);

        for (int j = 0; j < distance; j++) {
            output << "  ";
        }

        for (int j = distance; j < rows - distance; j++) {
            if (j > distance) {
                output << " ";
            }

            int value = vector_get(vec, i * rows + j);

            if (value == PATH) {
                output << "#";
            } else {
                output << value;
            }
        }
        output << '\n';
    }
}
