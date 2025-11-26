#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "queue.h"

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

int encode(int x, int y, int cols) {
    return x * cols + y;
}

void decode(int code, int cols, int& x, int& y) {
    x = code / cols;
    y = code % cols;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Error: File not specified" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << "Error: Cannot open file " << argv[1] << endl;
        return 1;
    }

    vector<string> maze;
    string line;
    while (getline(file, line)) {
        maze.push_back(line);
    }
    file.close();

    if (maze.empty()) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    size_t rows = maze.size();
    size_t cols = maze[0].size();

    Point start(-1, -1), end(-1, -1);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (maze[i][j] == 'X') {
                start = Point((int)i, (int)j);
            }
            else if (maze[i][j] == 'Y') {
                end = Point((int)i, (int)j);
            }
        }
    }

    if (start.x == -1 || end.x == -1) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    vector<vector<Point>> previous(rows, vector<Point>(cols, Point(-1, -1)));

    int dx[] = { -1, 0, 1, 0 };
    int dy[] = { 0, 1, 0, -1 };

    Queue* queue = queue_create();

    previous[start.x][start.y] = Point(start.x, start.y);
    queue_insert(queue, encode(start.x, start.y, (int)cols));

    bool found = false;

    while (!queue_empty(queue)) {
        int current_code = queue_get(queue);
        queue_remove(queue);

        int x, y;
        decode(current_code, (int)cols, x, y);

        if (x == end.x && y == end.y) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nextX = x + dx[i];
            int nextY = y + dy[i];

            if (isValid(nextX, nextY, (int)rows, (int)cols) &&
                maze[nextX][nextY] != '#' &&
                previous[nextX][nextY].x == -1) {

                previous[nextX][nextY] = Point(x, y);
                queue_insert(queue, encode(nextX, nextY, (int)cols));
            }
        }
    }

    queue_delete(queue);

    if (!found) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    vector<string> result = maze;
    Point current = end;

    while (!(current.x == start.x && current.y == start.y)) {
        if (!(current.x == end.x && current.y == end.y) &&
            !(current.x == start.x && current.y == start.y)) {
            result[current.x][current.y] = 'x';
        }
        current = previous[current.x][current.y];
    }

    for (size_t i = 0; i < rows; ++i) {
        cout << result[i] << endl;
    }

    return 0;
}