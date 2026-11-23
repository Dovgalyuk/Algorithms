#include "../../LibraryCPP/queue.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using Maze = std::vector<std::string>;

bool readMaze(const char* filename, Maze& maze) {
    std::ifstream input(filename);

    if (!input.is_open()) {
        return false;
    }

    std::string line;

    while (std::getline(input, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (!line.empty()) {
            maze.push_back(line);
        }
    }

    if (maze.empty()) {
        return false;
    }

    size_t width = maze[0].size();
    int startCount = 0;
    int finishCount = 0;

    for (const std::string& row : maze) {
        if (row.size() != width) {
            return false;
        }

        for (char cell : row) {
            if (cell == 'X') {
                startCount++;
            } else if (cell == 'Y') {
                finishCount++;
            } else if (cell != '.' && cell != '#') {
                return false;
            }
        }
    }

    return startCount == 1 && finishCount == 1;
}

int findStart(const Maze& maze) {
    int width = static_cast<int>(maze[0].size());

    for (int i = 0; i < static_cast<int>(maze.size()); i++) {
        for (int j = 0; j < width; j++) {
            if (maze[i][j] == 'X') {
                return i * width + j;
            }
        }
    }

    return -1;
}

bool isValidCell(const Maze& maze, int row, int col, const std::vector<bool>& visited) {
    int height = static_cast<int>(maze.size());
    int width = static_cast<int>(maze[0].size());

    if (row < 0 || row >= height ||
        col < 0 || col >= width) {
        return false;
    }

    if (maze[row][col] == '#') {
        return false;
    }

    return !visited[row * width + col];
}

int findPath(const Maze& maze, int start, std::vector<int>& parent) {
    int width = static_cast<int>(maze[0].size());
    int height = static_cast<int>(maze.size());

    std::vector<bool> visited(height * width, false);

    Queue* queue = queue_create();

    queue_insert(queue, start);
    visited[start] = true;

    const int dr[] = {-1, 1, 0, 0};
    const int dc[] = {0, 0, -1, 1};

    int finish = -1;

    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove(queue);

        int row = current / width;
        int col = current % width;

        if (maze[row][col] == 'Y') {
            finish = current;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int newRow = row + dr[i];
            int newCol = col + dc[i];

            if (!isValidCell(maze, newRow, newCol, visited)) {
                continue;
            }

            int next = newRow * width + newCol;

            visited[next] = true;
            parent[next] = current;

            queue_insert(queue, next);
        }
    }

    queue_delete(queue);

    return finish;
}

void restorePath(Maze& maze, int start, int finish, const std::vector<int>& parent) {
    int width = static_cast<int>(maze[0].size());
    int current = parent[finish];

    while (current != start) {
        int row = current / width;
        int col = current % width;

        maze[row][col] = 'x';
        current = parent[current];
    }
}

void printMaze(const Maze& maze) {
    for (const std::string& row : maze) {
        std::cout << row << '\n';
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }

    Maze maze;

    if (!readMaze(argv[1], maze)) {
        return 1;
    }

    int start = findStart(maze);

    if (start == -1) {
        return 1;
    }

    int width = static_cast<int>(maze[0].size());

    std::vector<int> parent(maze.size() * width, -1);

    int finish = findPath(maze, start, parent);

    if (finish == -1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    restorePath(maze, start, finish, parent);
    printMaze(maze);

    return 0;
}
