#include <iostream>
#include <fstream>
#include "queue.h"
#include "vector.h"


struct Point {
    size_t row;
    size_t col;
};


using namespace std;

const char WALL = '#';
const char EMPTY = '.';
const char START = 'X';
const char FINISH = 'Y';
const char PATH = 'x';


Vector* readMaze(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return nullptr;
    }

    Vector* maze = vector_create();
    char c;

    size_t capacity = 0;
    while (file.get(c)) {
        if (c != '\n') {
            ++capacity;
        }
    }

    file.clear();
    file.seekg(0, ios::beg);
    vector_resize(maze, capacity);

    size_t index = 0;
    while (file.get(c)) {
        if (c != '\n') {
            vector_set(maze, index++, c);
        }
    }

    file.close();
    return maze;
}



void printMaze(const Vector* maze) {
    for (size_t i = 0; i < vector_size(maze); ++i) {
        char c = vector_get(maze, i);
        if (c == '\n') {
            cout << std::endl;
        } else {
            cout << c;
        }
    }
}

bool findPath(Vector* maze) {
    Queue* queue = queue_create();
    Point start;
    for (size_t i = 0; i < vector_size(maze); ++i) {
        if (vector_get(maze, i) == START) {
            start.row = i / (vector_size(maze) + 1);
            start.col = i % (vector_size(maze) + 1);
            break;
        }
    }

    queue_insert(queue, static_cast<Data>(PATH));

    while (!queue_empty(queue)) {
        queue_remove(queue);

    }

    queue_delete(queue);
    return false;
}
int main() {
    const char* filename = "input.txt";  
    Vector* maze = readMaze(filename);

    if (maze) {
        if (findPath(maze)) {
            printMaze(maze);
        } else {
            cout << "IMPOSSIBLE" << std::endl;
        }

        vector_delete(maze);
    }

    return 0;
}