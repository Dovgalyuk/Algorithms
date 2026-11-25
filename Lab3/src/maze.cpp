#include "maze.h"
#include "queue.h"

#include <iostream>

bool readMaze(FILE* input, Maze& maze) {
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), input)) {
        std::string line = buffer;

        if (!line.empty() && line.back() == '\n')
            line.pop_back();

        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        if (!line.empty())
            maze.push_back(line);
    }

    return !maze.empty();
}

int findStart(const Maze& maze) {
    int width = maze[0].size();

    for (int i = 0; i < (int)maze.size(); i++) {
        for (int j = 0; j < width; j++) {
            if (maze[i][j] == 'X')
                return i * width + j;
        }
    }

    return -1;
}

bool checkCell(const Maze& maze, int row, int col, const std::vector<bool>& visited) {
    int height = maze.size();
    int width = maze[0].size();

    if (row < 0 || row >= height || col < 0 || col >= width)
        return false;

    if (maze[row][col] == '#')
        return false;

    if (visited[row * width + col])
        return false;

    return true;
}

bool findPath(const Maze& maze, int start, std::vector<int>& parent) {
    int height = maze.size();
    int width = maze[0].size();

    std::vector<bool> visited(height * width, false);

    Queue* queue = queue_create();

    queue_insert(queue, start);
    visited[start] = true;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    bool found = false;

    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove(queue);

        int row = current / width;
        int col = current % width;

        if (maze[row][col] == 'Y') {
            found = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int newRow = row + dr[i];
            int newCol = col + dc[i];

            if (!checkCell(maze, newRow, newCol, visited))
                continue;

            int next = newRow * width + newCol;

            visited[next] = true;
            parent[next] = current;

            queue_insert(queue, next);
        }
    }

    queue_delete(queue);

    return found;
}

void restorePath(Maze& maze, int start, int finish, const std::vector<int>& parent) {
    int width = maze[0].size();

    int current = parent[finish];

    while (current != start) {
        int row = current / width;
        int col = current % width;

        maze[row][col] = 'x';

        current = parent[current];
    }
}

void printMaze(const Maze& maze) {
    for (const std::string& row : maze)
        std::cout << row << '\n';
}