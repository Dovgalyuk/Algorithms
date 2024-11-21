#include "alg_lab3.h"
#include "queue.h"

bool is_valid(int row, int col, const Maze& maze, const std::vector<std::vector<bool>>& visited) {
    return row >= 0 && row < static_cast<int>(maze.size()) &&
           col >= 0 && col < static_cast<int>(maze[0].size()) &&
           maze[row][col] != '#' && !visited[row][col];
}

void bfs(Maze& maze, Point start, Point end, bool& solvable) {
    const std::vector<Point> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int rows = maze.size();
    int cols = maze[0].size();

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::vector<std::vector<Point>> parent(rows, std::vector<Point>(cols, {-1, -1}));

    Queue queue;
    queue.insert(start.row * cols + start.col);
    visited[start.row][start.col] = true;

    while (!queue.empty()) {
        int encoded = queue.get();
        queue.remove();

        Point current = {encoded / cols, encoded % cols};

        if (current == end) {
            solvable = true;
            break;
        }

        for (const auto& d : directions) {
            int new_row = current.row + d.row;
            int new_col = current.col + d.col;

            if (is_valid(new_row, new_col, maze, visited)) {
                visited[new_row][new_col] = true;
                parent[new_row][new_col] = current;
                queue.insert(new_row * cols + new_col);
            }
        }
    }

    if (solvable) {
        Point p = end;
        while (!(p == start)) {
            maze[p.row][p.col] = 'x';
            p = parent[p.row][p.col];
        }
        if (maze[start.row][start.col] != 'X') {
            maze[start.row][start.col] = 'X';
        }
        maze[end.row][end.col] = 'Y';
    }
}