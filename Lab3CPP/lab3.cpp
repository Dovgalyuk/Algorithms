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

void bfs(vector<string>& maze, Point start, Point end) {
  
    int rows = static_cast<int>(maze.size());
    if (rows == 0) return;
    int cols = static_cast<int>(maze[0].size());

   
    int dx[] = { -1, 0, 1, 0 };
    int dy[] = { 0, 1, 0, -1 };

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<Point>> parent(rows, vector<Point>(cols, Point(-1, -1)));

    Queue* queue = queue_create();


    queue_insert(queue, start.x * cols + start.y);
    visited[start.x][start.y] = true;

    bool found = false;

    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove(queue);

        int x = current / cols;
        int y = current % cols;

        if (x == end.x && y == end.y) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny, rows, cols) && !visited[nx][ny] && maze[nx][ny] != '#') {
                visited[nx][ny] = true;
                parent[nx][ny] = Point(x, y);
                queue_insert(queue, nx * cols + ny);
            }
        }
    }

    if (found) {

        Point current = end;
        while (!(current.x == start.x && current.y == start.y)) {
            if (maze[current.x][current.y] == '.') {
                maze[current.x][current.y] = 'x';
            }
            current = parent[current.x][current.y];
        }

        for (const auto& row : maze) {
            cout << row << endl;
        }
    }
    else {
        cout << "IMPOSSIBLE" << endl;
    }

    queue_delete(queue);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Error: Cannot open input file " << argv[1] << endl;
        return 1;
    }

    vector<string> maze;
    string line;

    while (getline(input, line)) {
        maze.push_back(line);
    }
    input.close();

    if (maze.empty()) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    Point start, end;
    bool found_start = false, found_end = false;

    for (int i = 0; i < static_cast<int>(maze.size()); i++) {
        for (int j = 0; j < static_cast<int>(maze[i].size()); j++) {
            if (maze[i][j] == 'X') {
                start = Point(i, j);
                found_start = true;
            }
            else if (maze[i][j] == 'Y') {
                end = Point(i, j);
                found_end = true;
            }
        }
    }

    if (!found_start || !found_end) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    bfs(maze, start, end);

    return 0;
}