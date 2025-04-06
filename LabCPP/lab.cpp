#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include "queue.h"

using namespace std;

struct BoardState {
    string state;
    string path;
};

static int step_counter = 0;

vector<string> get_neighbors(const string& current) {
    vector<string> neighbors;
    const size_t zero_pos = current.find('0');
    if (zero_pos == string::npos) {
        throw runtime_error("Invalid state: no empty position (0) found");
    }

    const int x = static_cast<int>(zero_pos % 3);
    const int y = static_cast<int>(zero_pos / 3);

    const int dx[] = { -1, 1, 0, 0 };
    const int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; i++) {
        const int nx = x + dx[i];
        const int ny = y + dy[i];

        if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
            string next = current;
            const size_t swap_pos = static_cast<size_t>(ny * 3 + nx);
            swap(next[zero_pos], next[swap_pos]);
            neighbors.push_back(next);
        }
    }
    return neighbors;
}

vector<string> solve_puzzle8(const string& initial) {
    const string goal = "123456780";
    Queue* queue = queue_create();
    unordered_map<string, bool> visited;
    vector<string> solution;
    vector<BoardState> states;

    // Проверка начального состояния
    if (initial.length() != 9) {
        throw runtime_error("Invalid initial state length");
    }

    states.push_back({ initial, "" });
    queue_insert(queue, 0);

    while (!queue_empty(queue)) {
        int current_idx = queue_get(queue);
        queue_remove(queue);
        BoardState current = states[current_idx];

        if (current.state == goal) {
            // Восстановление пути
            string state = initial;
            solution.push_back(state);
            for (char move : current.path) {
                size_t zero_pos = state.find('0');
                if (zero_pos == string::npos) break;

                size_t new_pos = zero_pos;
                switch (move) {
                case 'U':
                    if (zero_pos >= 3) new_pos = zero_pos - 3;
                    break;
                case 'D':
                    if (zero_pos + 3 < 9) new_pos = zero_pos + 3;
                    break;
                case 'L':
                    if (zero_pos % 3 > 0) new_pos = zero_pos - 1;
                    break;
                case 'R':
                    if (zero_pos % 3 < 2) new_pos = zero_pos + 1;
                    break;
                }
                // Дополнительная проверка
                if (new_pos < state.length()) {
                    swap(state[zero_pos], state[new_pos]);
                    solution.push_back(state);
                }
            }
            break;
        }

        if (visited[current.state]) continue;
        visited[current.state] = true;

        size_t zero_pos = current.state.find('0');
        if (zero_pos == string::npos) continue;

        // Генерация соседних состояний с проверками
        const int directions[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
        const char dir_chars[] = { 'L', 'R', 'U', 'D' };

        for (int i = 0; i < 4; i++) {
            int x = static_cast<int>(zero_pos % 3) + directions[i][0];
            int y = static_cast<int>(zero_pos / 3) + directions[i][1];

            if (x >= 0 && x < 3 && y >= 0 && y < 3) {
                string next = current.state;
                size_t swap_pos = static_cast<size_t>(y * 3 + x);

                // Проверка перед обменом
                if (swap_pos < next.length() && zero_pos < next.length()) {
                    swap(next[zero_pos], next[swap_pos]);

                    if (!visited[next]) {
                        states.push_back({ next, current.path + dir_chars[i] });
                        if (states.size() > INT_MAX) {
                            throw runtime_error("Too many states generated");
                        }
                        queue_insert(queue, static_cast<int>(states.size() - 1));
                    }
                }
            }
        }
    }

    queue_delete(queue);
    return solution;
}

void print_board(const string& state) {
    cout << "Шаг " << step_counter++ << ":" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            const char c = state[i * 3 + j];
            if (c == '0') cout << "  ";
            else cout << c << " ";
        }
        cout << endl;
    }
    cout << "-----" << endl;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    string initial;
    if (argc >= 2) {
        ifstream inputFile(argv[1]);
        if (!inputFile) {
            cerr << "Ошибка: не удалось открыть файл " << argv[1] << endl;
            return 1;
        }
        inputFile >> initial;
    }
    else {
        cout << "Введите начальное состояние (9 цифр, 0 для пустой клетки): ";
        cin >> initial;
    }

    if (initial.length() != 9) {
        cerr << "Ошибка: требуется ровно 9 цифр (0-8)." << endl;
        return 1;
    }

    try {
        vector<string> solution = solve_puzzle8(initial);
        cout << "\nПуть решения (" << solution.size() - 1 << " ходов):\n";
        for (const string& state : solution) {
            print_board(state);
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}