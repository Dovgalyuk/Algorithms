#include <iostream>
#include <fstream>
#include "queue.h"

const int MAX_SIZE = 100;

struct Point {
    int x, y;
};

int bfs(char maze[MAX_SIZE][MAX_SIZE], Point start, int rows, int cols) {
    Queue* queue = queue_create();
    bool visited[MAX_SIZE][MAX_SIZE] = {false};
    int distance[MAX_SIZE][MAX_SIZE];

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            distance[i][j] = -1;
        }
    }

    queue_insert(queue, start);
    distance[start.x][start.y] = 0;
    visited[start.x][start.y] = true;

    while (!queue_empty(queue)) {
        Point current = queue_get(queue);
        queue_remove(queue);

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
                maze[newX][newY] != '#' && !visited[newX][newY]) {
                queue_insert(queue, {newX, newY});
                distance[newX][newY] = distance[current.x][current.y] + 1;
                visited[newX][newY] = true;
            }
        }
    }

    int minDistance = MAX_SIZE * MAX_SIZE;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] >= '0' && maze[i][j] <= '9') {
                minDistance = std::min(minDistance, distance[i][j]);
            }
        }
    }

    return minDistance;
}

int main() {
    std::ifstream input("input.txt");
    int rows, cols;
    input >> rows >> cols;
    char maze[MAX_SIZE][MAX_SIZE];

    Point start;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            input >> maze[i][j];
            if (maze[i][j] == 'X') {
                start.x = i;
                start.y = j;
            }
        }
    }

    int result = bfs(maze, start, rows, cols);
    std::cout << result << std::endl;

    return 0;
}
