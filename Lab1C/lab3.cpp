#include <iostream>
#include <fstream>
#include <vector>
#include <queue> 

#include "queue.h"
#include "vector.h"

using namespace std;
struct Point {
    int x, y;
};

struct Maze {
    vector<string> grid;
    Point start, finish;
};

void read_maze(const char *filename, Maze &maze);
void print_maze(const Maze &maze);
bool solve_maze(Maze &maze);

void read_maze(const char *filename, Maze &maze) {
    ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    string line;
    int row = 0;

    while (std::getline(file, line)) {
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
    queue<Point> q;
    q.push(maze.start);

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        if (current.x < 0 || current.y < 0 || current.x >= maze.grid.size() || current.y >= maze.grid[0].size()) {
            continue;  
        }

        char &cell = maze.grid[current.x][current.y];

        if (cell == 'Y') {
            return true;  
        }

        if (cell == '.' || cell == 'X') {
            cell = 'x';  

            q.push({current.x + 1, current.y});
            q.push({current.x - 1, current.y});
            q.push({current.x, current.y + 1});
            q.push({current.x, current.y - 1});
        }
    }

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