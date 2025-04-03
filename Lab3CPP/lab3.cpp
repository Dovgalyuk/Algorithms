#include <iostream>
#include <unordered_set>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cstdio>

#include "queue.h"

using namespace std;

// Функция для преобразования в одно число, представляющее доску
long to_long(const vector<int>& board) {
    long long result = 0;
    for (int i = 0; i < 9; ++i) {
        result = result * 10 + board[i];
    }
    return result;
}

// Функция для преобразования числа в доску
vector<int> to_board(long number) {
    vector<int> board(9);
    for (int i = 8; i >= 0; --i) {
        board[i] = number % 10;
        number /= 10;
    }
    return board;
}

// Функция для генерации всех возможных соседей текущего состояния доски
vector<long> get_neighbors(const vector<int>& board) {
    vector<long> neighbors;
    int zero_pos = std::find(board.begin(), board.end(), 0) - board.begin(); // Позиция пустого места (ноль)
    int row = zero_pos / 3;
    int col = zero_pos % 3;

    // Возможности для перемещения пустого места: влево, вправо, вверх, вниз
    vector<pair<int, int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    for (auto& dir : directions) {
        int new_row = row + dir.first;
        int new_col = col + dir.second;

        // Проверяем, что новое положение допустимо
        if (new_row >= 0 && new_row < 3 && new_col >= 0 && new_col < 3) {
            int new_zero_pos = new_row * 3 + new_col;
            vector<int> new_board = board;
            swap(new_board[zero_pos], new_board[new_zero_pos]);
            neighbors.push_back(to_long(new_board));  // Преобразуем доску обратно в число
        }
    }
    return neighbors;
}

// Функция для вывода состояния доски
void print_board(const vector<int>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i * 3 + j] << " ";
        }
        cout << endl;
    }
    cout << endl;  // Добавляем пустую строку для разделения этапов
}

// Функция для поиска решения головоломки с помощью BFS
void solve_puzzle(vector<int> start) {
    vector<int> goal_board = {1, 2, 3, 4, 5, 6, 7, 8, 0};  // Целевое состояние
    long goal = to_long(goal_board);

    long start_long = to_long(start);
    if (start_long == goal) {
        print_board(start);
        return;
    }

    Queue* q = queue_create();  // Создаём очередь
    unordered_set<long> visited;  // Множество посещённых состояний

    // Инициализируем очередь с начальной позицией
    queue_insert(q, start_long);
    visited.insert(start_long);

    // Будем хранить путь до текущего состояния
    unordered_map<long, long> parent_map;
    parent_map[start_long] = -1;  // Начальная позиция не имеет родителя

    while (!queue_empty(q)) {
        long current_board_long = queue_get(q);
        queue_remove(q);
        vector<int> current_board = to_board(current_board_long);

        // Генерируем все соседние состояния
        for (long neighbor : get_neighbors(current_board)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                queue_insert(q, neighbor);
                parent_map[neighbor] = current_board_long;

                if (neighbor == goal) {
                    // Если достигли целевого состояния, восстанавливаем путь
                    vector<long> solution_path;
                    for (long state = goal; state != -1; state = parent_map[state]) {
                        solution_path.push_back(state);
                    }

                    // Выводим решение
                    for (auto it = solution_path.rbegin(); it != solution_path.rend(); ++it) {
                        print_board(to_board(*it));
                    }
                    return;
                }
            }
        }
    }

    cout << "No solution has been found." << endl;
    queue_delete(q);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Error: specify the input data file.\n");
        return 1;
    }

    FILE* input = nullptr;
    if (fopen_s(&input, argv[1], "r") != 0 || input == nullptr) {
        printf("Error: couldn't open the file %s.\n", argv[1]);
        return 1;
    }

    char start_str[10];
    if (fscanf_s(input, "%9s", start_str, sizeof(start_str)) != 1) {
        printf("Error: data could not be read from the file.\n");
        fclose(input);
        return 1;
    }
    fclose(input);

    if (strlen(start_str) != 9) {
        cout << "Error: The status must contain 9 characters." << endl;
        return 1;
    }

    vector<int> start(9);
    for (int i = 0; i < 9; ++i) {
        start[i] = start_str[i] - '0';
    }

    solve_puzzle(start);

    return 0;
}