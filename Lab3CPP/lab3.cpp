#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <climits>
#include "queue.h"

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};
typedef std::vector<std::string> Maze;

int findNearestDigit(const Maze& maze, Point start) {
    int rows = maze.size();
    if (rows == 0) return -1;
    int cols = maze[0].size();

    int dx[] = { -1, 0, 1, 0 };
    int dy[] = { 0, 1, 0, -1 };

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::vector<std::vector<int>> distance(rows, std::vector<int>(cols, INT_MAX));

    Queue* queue = queue_create();

    queue_insert(queue, start.x);
    queue_insert(queue, start.y);
    visited[start.x][start.y] = true;
    distance[start.x][start.y] = 0;

    int nearestDigit = -1;
    int minDistance = INT_MAX;

    while (!queue_empty(queue)) {
        int x = queue_get(queue);
        queue_remove(queue);
        int y = queue_get(queue);
        queue_remove(queue);

        if (std::isdigit(maze[x][y])) {
            int digit = maze[x][y] - '0';

            if (distance[x][y] < minDistance) {
                minDistance = distance[x][y];
                nearestDigit = digit;
                break;
            }
        }
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
                maze[nx][ny] != '#' && !visited[nx][ny]) {

                visited[nx][ny] = true;
                distance[nx][ny] = distance[x][y] + 1;
                queue_insert(queue, nx);
                queue_insert(queue, ny);
            }
        }
    }
    queue_delete(queue);
    return nearestDigit;
}
int main(int argc, char* argv[]) {
    std::string filename = "input.txt";

    if (argc > 1) {
        filename = argv[1];
    }
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Cannot open input file: " << filename << std::endl;
        return 1;
    }
    Maze maze;
    std::string line;
    Point start(-1, -1);

    size_t row = 0;
    while (std::getline(inputFile, line)) {
        maze.push_back(line);

        for (size_t col = 0; col < line.length(); ++col) {
            if (line[col] == 'X') {
                start.x = static_cast<int>(row);
                start.y = static_cast<int>(col);
            }
        }
        row++;
    }
    inputFile.close();

    if (start.x == -1 || start.y == -1) {
        std::cerr << "Start position 'X' not found in " << filename << "!" << std::endl;
        return 1;
    }
    int result = findNearestDigit(maze, start);

    if (result != -1) {
        std::cout << result << std::endl;
    }
    else {
        std::cout << "No digits found in the maze!" << std::endl;
    }
    return 0;
}