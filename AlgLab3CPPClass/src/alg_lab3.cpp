#include "alg_lab3.h"
#include "queue.h"

bool is_valid(int x, int y, const std::vector<std::string>& maze, const std::vector<std::vector<bool>>& visited) {
    return x >= 0 && x < static_cast<int>(maze.size()) &&
           y >= 0 && y < static_cast<int>(maze[0].size()) &&
           maze[x][y] != '#' && !visited[x][y];
}

void bfs(std::vector<std::string>& maze, Point start, Point end, bool& solvable) {
    const std::vector<Point> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int rows = maze.size();
    int cols = maze[0].size();

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::vector<std::vector<Point>> parent(rows, std::vector<Point>(cols, {-1, -1}));

    Queue queue;
    queue.insert(start.x * cols + start.y);
    visited[start.x][start.y] = true;

    while (!queue.empty()) {
        int encoded = queue.get();
        queue.remove();

        Point current = {encoded / cols, encoded % cols};

        if (current == end) {
            Point p = end;
            while (!(p == start)) {
                maze[p.x][p.y] = 'x';
                p = parent[p.x][p.y];
            }
            maze[start.x][start.y] = 'X';
            maze[end.x][end.y] = 'Y';
            solvable = true;
            return;
        }

        for (const auto& d : directions) {
            int nx = current.x + d.x;
            int ny = current.y + d.y;

            if (is_valid(nx, ny, maze, visited)) {
                visited[nx][ny] = true;
                parent[nx][ny] = current;
                queue.insert(nx * cols + ny);
            }
        }
    }

    solvable = false;
}