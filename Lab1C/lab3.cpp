#include <iostream>
#include <fstream>
#include <vector>
#include "queue.h"
#include "vector.h"

using namespace std;

struct Maze {
    vector<string> grid;
    pair<int, int> start, finish;
};


void read_maze(const char *filename, Maze &maze) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    int row = 0;

    while (getline(file, line)) {
        maze.grid.push_back(line);

        size_t col = line.find('X');
        if (col != string::npos) {
            maze.start = {static_cast<int>(row), static_cast<int>(col)};
        }

        col = line.find('Y');
        if (col != string::npos) {
            maze.finish = {static_cast<int>(row), static_cast<int>(col)};
        }

        ++row;
    }

    file.close();
}

void print_maze(const Maze &maze) {
    for (const auto &row : maze.grid) {
        cout << row << endl;
    }
}

bool solve_maze(Maze &maze) {
    Queue *q = queue_create();
    queue_enqueue(q, maze.start);

    while (!queue_empty(q)) {
        pair<int, int> current = queue_dequeue(q);

        if (current == maze.finish) {
            queue_delete(q);
            return true;
        }

        if (current.first < 0 || current.second < 0 || static_cast<size_t>(current.first) >= maze.grid.size() ||
            static_cast<size_t>(current.second) >= maze.grid[0].size()) {
            continue;
        }

        char &cell = maze.grid[current.first][current.second];

        if (cell == 'Y') {
            queue_delete(q);
            return true;
        }

        if (cell == '.' || cell == 'X') {
            cell = 'x';

            queue_enqueue(q, {current.first + 1, current.second});
            queue_enqueue(q, {current.first - 1, current.second});
            queue_enqueue(q, {current.first, current.second + 1});
            queue_enqueue(q, {current.first, current.second - 1});
        }
    }

    queue_delete(q);
    return false;
}


int main() {
    Maze maze;
    read_maze("input.txt", maze);

    if (solve_maze(maze)) {
        print_maze(maze);
    } else {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}

