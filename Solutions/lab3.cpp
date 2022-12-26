//
// Created by Artem Raykh on 25.12.2022.
//

#include <iostream>
#include <fstream>
#include "queue.h"
#include "vector.h"

void streamOut(Vector *distance, int end) {

    std::ofstream outputStream("output.txt");

    if (vector_get(distance, end - 1) == 0) {
        outputStream << "IMPOSSIBLE";
    } else {
        outputStream << vector_get(distance, end - 1);
    }

    outputStream.close();
}

void breadthFirstSearch(int** graphMatrix, int graphSize, int initial, int end) {

    Queue *visited = queue_create();
    Vector *distance = vector_create();

    for (int i = 0; i < graphSize; i++) {
        vector_set(distance, i, 0);
    }

    queue_insert(visited, initial - 1);

    while (!queue_empty(visited)) {

        int lastItem = queue_get(visited);
        queue_remove(visited);

        for (int i = 0; i < graphSize; i++) {
            if ((graphMatrix[lastItem][i] == 1) &&
                    (vector_get(distance, i) == 0) &&
                    (i != (initial - 1))) {
                queue_insert(visited, i);
                vector_set(
                        distance,
                        i,
                        vector_get(distance, lastItem) + 1
                        );
            }
        }
    }

    streamOut(distance, end);

    vector_delete(distance);
    queue_delete(visited);
}

int **getMatrix(std::istream &stream, int size) {

    int **matrix = new int* [size];

    int first, second;

    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++) {
            matrix[i][j] = 0;
        }
    }

    while (!stream.eof()) {
        stream >> first;
        stream >> second;
        matrix[first - 1][second - 1] = 1;
        matrix[second - 1][first - 1] = 1;
    }

    return matrix;
}

int main() {

    std::string filePath;

    std::cout << "Enter path to a file: " << std::endl;

    std::getline(std::cin, filePath);

    std::ifstream stream(filePath);

    if (!stream.is_open()) {
        std::cout << "File opening error" << std::endl;
        stream.close();
        return -1;
    }

    int size, initial, end;

    stream >> size;
    stream >> initial;
    stream >> end;

    int **matrix = getMatrix(stream, size);

    stream.close();

    breadthFirstSearch(matrix, size, initial, end);

    delete[] matrix;
}