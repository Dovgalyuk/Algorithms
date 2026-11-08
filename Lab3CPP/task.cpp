#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "queue.h"
#include "vector.h"
#include "task.h"

int reader(Vector* vec) {
    std::string line;
    Vector* values = vector_create();

    int rows = 0;

    while (std::getline(std::cin, line)) {
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
        vector_set(vec, i, -1);
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

