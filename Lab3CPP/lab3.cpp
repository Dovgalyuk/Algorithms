#include <iostream>
#include <fstream>
#include <vector>
#include "queue.h"
#include "vector.h"

struct Position {
    int row;
    int col;
};

// Используем size_t для работы с большими числами
size_t encode_position(int row, int col, size_t num_cols) {
    return static_cast<size_t>(row) * num_cols + col;
}

Position decode_position(size_t encoded, size_t num_cols) {
    Position pos;
    pos.row = static_cast<int>(encoded / num_cols);
    pos.col = static_cast<int>(encoded % num_cols);
    return pos;
}

bool is_valid_move(const std::vector<std::string>& maze, int row, int col) {
    return row >= 0 && static_cast<size_t>(row) < maze.size() &&
           col >= 0 && static_cast<size_t>(col) < maze[0].size() && maze[row][col] == '.';
}

int bfs(std::vector<std::string>& maze, Position start) {
    int reachable_cells = 0;
    Queue* queue = queue_create();
    size_t num_cols = maze[0].size();

    // Приводим к int перед вставкой в очередь
    queue_insert(queue, static_cast<int>(encode_position(start.row, start.col, num_cols)));
    maze[start.row][start.col] = 'x';

    while (!queue_empty(queue)) {
        Position current = decode_position(queue_get(queue), num_cols);
        queue_remove(queue);
        reachable_cells++;

        Position directions[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; ++i) {
            int new_row = current.row + directions[i].row;
            int new_col = current.col + directions[i].col;
            if (is_valid_move(maze, new_row, new_col)) {
                maze[new_row][new_col] = 'x';
                // Приводим к int перед вставкой в очередь
                queue_insert(queue, static_cast<int>(encode_position(new_row, new_col, num_cols)));
            }
        }
    }
    queue_delete(queue);
    return reachable_cells;
}

int main() {
    std::ifstream input("input.txt");
    if (!input.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл input.txt\n";
        return 1;
    }

    std::vector<std::string> maze;
    std::string line;
    Position start = {-1, -1};

    while (std::getline(input, line)) {
        maze.push_back(line);
    }
    input.close();

    // Поиск стартовой позиции
    bool start_found = false;
    for (size_t i = 0; i < maze.size(); ++i) {
        for (size_t j = 0; j < maze[i].size(); ++j) {
            if (maze[i][j] == 'X') {
                start.row = static_cast<int>(i);  // Приведение к int
                start.col = static_cast<int>(j);  // Приведение к int
                start_found = true;
                break;
            }
        }
        if (start_found) break;
    }

    if (!start_found) {
        std::cerr << "Ошибка: стартовая позиция 'X' не найдена в лабиринте\n";
        return 1;
    }

    int reachable_cells = bfs(maze, start);
    std::cout << reachable_cells << "\n";

    for (size_t i = 0; i < maze.size(); ++i) {
        std::cout << maze[i] << "\n";
    }
}
